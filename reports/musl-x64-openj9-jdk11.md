---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-28 17:44:03 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 999 |
| Sample Rate | 16.65/sec |
| Health Score | 1041% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 77-82 cores)</summary>

```
1777412449 77
1777412454 77
1777412459 77
1777412464 77
1777412469 77
1777412474 77
1777412479 77
1777412484 77
1777412489 81
1777412494 81
1777412499 81
1777412504 81
1777412509 81
1777412514 81
1777412519 81
1777412524 81
1777412529 81
1777412534 80
1777412539 80
1777412544 82
```
</details>

---

