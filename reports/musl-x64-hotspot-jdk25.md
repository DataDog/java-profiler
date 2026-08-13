---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-13 15:42:56 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 832 |
| Sample Rate | 13.87/sec |
| Health Score | 867% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1786649877 30
1786649882 30
1786649887 30
1786649892 30
1786649897 30
1786649902 28
1786649907 28
1786649912 28
1786649917 28
1786649922 28
1786649927 28
1786649932 28
1786649937 30
1786649942 30
1786649947 30
1786649952 30
1786649957 32
1786649962 32
1786649967 32
1786649972 32
```
</details>

---

