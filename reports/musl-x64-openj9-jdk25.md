---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 07:22:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 47-58 cores)</summary>

```
1793621902 47
1793621907 47
1793621912 47
1793621917 47
1793621922 58
1793621927 58
1793621932 58
1793621937 58
1793621942 58
1793621947 58
1793621952 58
1793621957 58
1793621962 58
1793621967 58
1793621972 58
1793621977 58
1793621982 58
1793621987 58
1793621992 58
1793621997 58
```
</details>

---

