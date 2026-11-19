---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:28:40 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 11 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (4 unique values: 65-77 cores)</summary>

```
1795108867 65
1795108872 65
1795108877 65
1795108882 65
1795108887 65
1795108892 65
1795108897 65
1795108902 65
1795108907 73
1795108912 73
1795108917 73
1795108922 73
1795108927 73
1795108932 73
1795108937 73
1795108942 73
1795108947 73
1795108952 73
1795108957 73
1795108962 73
```
</details>

---

