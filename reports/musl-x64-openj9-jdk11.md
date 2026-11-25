---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 08:37:26 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 85 |
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
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 9 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1795613510 85
1795613515 85
1795613520 85
1795613525 85
1795613530 85
1795613535 85
1795613540 85
1795613545 85
1795613550 85
1795613555 85
1795613560 85
1795613565 83
1795613570 83
1795613575 83
1795613580 83
1795613585 83
1795613590 83
1795613595 85
1795613600 85
1795613605 85
```
</details>

---

