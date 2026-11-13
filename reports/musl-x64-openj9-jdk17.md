---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:44:22 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 57-59 cores)</summary>

```
1794584389 57
1794584394 57
1794584399 57
1794584404 57
1794584409 57
1794584414 57
1794584419 57
1794584424 59
1794584429 59
1794584434 59
1794584439 59
1794584444 59
1794584449 59
1794584454 59
1794584459 59
1794584464 59
1794584469 59
1794584474 59
1794584479 59
1794584484 59
```
</details>

---

