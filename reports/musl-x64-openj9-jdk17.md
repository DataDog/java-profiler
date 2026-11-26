---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 08:20:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (4 unique values: 49-56 cores)</summary>

```
1795698908 56
1795698913 56
1795698918 56
1795698923 56
1795698928 56
1795698933 49
1795698938 49
1795698943 51
1795698948 51
1795698953 49
1795698958 49
1795698963 49
1795698968 49
1795698973 49
1795698978 49
1795698983 49
1795698988 49
1795698993 49
1795698998 49
1795699003 55
```
</details>

---

