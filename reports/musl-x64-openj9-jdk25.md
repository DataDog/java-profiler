---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-12 05:55:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (5 unique values: 77-88 cores)</summary>

```
1791798661 77
1791798666 77
1791798671 77
1791798676 77
1791798681 77
1791798686 77
1791798691 77
1791798696 77
1791798701 77
1791798706 77
1791798711 77
1791798716 79
1791798721 79
1791798726 81
1791798731 81
1791798736 81
1791798741 81
1791798746 81
1791798751 81
1791798756 81
```
</details>

---

