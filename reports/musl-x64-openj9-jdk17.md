---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 05:58:34 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1793789555 59
1793789560 59
1793789565 59
1793789570 61
1793789575 61
1793789580 61
1793789585 61
1793789590 59
1793789595 59
1793789600 59
1793789605 59
1793789610 59
1793789615 59
1793789620 59
1793789625 61
1793789630 61
1793789635 63
1793789640 63
1793789645 63
1793789650 63
```
</details>

---

