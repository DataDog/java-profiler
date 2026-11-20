---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 05:51:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795171539 50
1795171544 50
1795171549 50
1795171554 50
1795171559 50
1795171564 50
1795171570 50
1795171575 50
1795171580 50
1795171585 50
1795171590 50
1795171595 50
1795171600 50
1795171605 50
1795171610 50
1795171615 50
1795171620 50
1795171625 50
1795171630 50
1795171635 50
```
</details>

---

