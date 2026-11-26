---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 09:24:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 19-25 cores)</summary>

```
1795702808 19
1795702813 19
1795702818 19
1795702823 19
1795702828 22
1795702833 22
1795702838 25
1795702843 25
1795702848 25
1795702853 25
1795702858 25
1795702863 25
1795702868 25
1795702873 25
1795702878 25
1795702883 25
1795702888 25
1795702893 25
1795702898 25
1795702903 25
```
</details>

---

