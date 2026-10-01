---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 11:00:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790866529 48
1790866534 48
1790866539 48
1790866544 48
1790866549 48
1790866554 48
1790866559 48
1790866564 48
1790866569 48
1790866574 48
1790866579 48
1790866584 48
1790866589 48
1790866594 48
1790866599 47
1790866604 47
1790866609 47
1790866615 47
1790866620 47
1790866625 47
```
</details>

---

