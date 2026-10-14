---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-14 04:13:56 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 317 |
| Sample Rate | 5.28/sec |
| Health Score | 330% |
| Threads | 14 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791965396 43
1791965401 43
1791965406 43
1791965411 43
1791965416 48
1791965421 48
1791965426 48
1791965431 48
1791965436 48
1791965441 48
1791965446 48
1791965451 48
1791965456 48
1791965461 48
1791965466 48
1791965471 48
1791965476 48
1791965481 48
1791965486 48
1791965491 48
```
</details>

---

