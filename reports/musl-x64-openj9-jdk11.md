---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:44:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 10 |
| Allocations | 579 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1794584403 59
1794584408 59
1794584413 59
1794584418 59
1794584423 59
1794584428 59
1794584433 59
1794584438 59
1794584443 59
1794584448 59
1794584453 59
1794584458 59
1794584463 59
1794584468 59
1794584473 59
1794584478 61
1794584483 61
1794584488 61
1794584493 61
1794584498 61
```
</details>

---

