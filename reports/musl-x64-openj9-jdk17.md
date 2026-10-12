---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-12 05:55:35 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1791798656 11
1791798661 11
1791798666 11
1791798671 11
1791798676 11
1791798681 11
1791798686 11
1791798691 11
1791798696 11
1791798701 11
1791798706 11
1791798711 11
1791798716 11
1791798721 11
1791798726 11
1791798731 32
1791798736 32
1791798741 32
1791798746 32
1791798751 32
```
</details>

---

