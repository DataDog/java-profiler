---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 17:11:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793656922 48
1793656927 48
1793656932 48
1793656937 48
1793656942 48
1793656947 48
1793656952 48
1793656957 48
1793656962 48
1793656967 48
1793656972 48
1793656977 48
1793656982 48
1793656987 48
1793656992 48
1793656997 48
1793657002 48
1793657007 48
1793657012 48
1793657017 48
```
</details>

---

