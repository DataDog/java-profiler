---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 09:59:32 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 37-57 cores)</summary>

```
1770130509 37
1770130514 37
1770130519 37
1770130524 37
1770130529 37
1770130534 37
1770130539 37
1770130544 37
1770130549 37
1770130554 37
1770130559 57
1770130564 57
1770130569 57
1770130574 57
1770130579 57
1770130584 57
1770130589 57
1770130594 57
1770130599 57
1770130604 57
```
</details>

---

