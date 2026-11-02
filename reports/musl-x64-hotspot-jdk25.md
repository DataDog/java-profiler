---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 17:11:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 22-41 cores)</summary>

```
1793656917 22
1793656922 22
1793656927 22
1793656932 22
1793656937 22
1793656942 22
1793656947 22
1793656952 22
1793656957 22
1793656962 22
1793656967 39
1793656972 39
1793656977 39
1793656982 39
1793656987 41
1793656992 41
1793656997 41
1793657002 41
1793657007 41
1793657012 41
```
</details>

---

