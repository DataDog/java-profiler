---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 05:33:21 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 53-69 cores)</summary>

```
1795602416 69
1795602421 69
1795602426 57
1795602431 57
1795602436 53
1795602441 53
1795602446 53
1795602451 53
1795602456 53
1795602461 53
1795602466 53
1795602471 53
1795602476 53
1795602481 53
1795602486 53
1795602491 53
1795602496 53
1795602501 53
1795602506 53
1795602511 53
```
</details>

---

