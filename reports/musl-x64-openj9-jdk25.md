---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 08:19:31 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 66 |
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
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 64-92 cores)</summary>

```
1795698854 90
1795698859 90
1795698864 90
1795698869 92
1795698874 92
1795698879 92
1795698884 92
1795698889 92
1795698894 92
1795698899 92
1795698904 92
1795698909 92
1795698914 92
1795698919 92
1795698924 92
1795698929 64
1795698934 64
1795698939 64
1795698944 64
1795698949 64
```
</details>

---

