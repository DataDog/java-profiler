---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-01 23:46:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793594504 48
1793594509 48
1793594514 48
1793594519 48
1793594524 48
1793594529 48
1793594534 48
1793594539 48
1793594544 48
1793594549 48
1793594554 48
1793594559 48
1793594564 46
1793594569 46
1793594574 46
1793594579 46
1793594584 46
1793594589 46
1793594594 46
1793594599 46
```
</details>

---

