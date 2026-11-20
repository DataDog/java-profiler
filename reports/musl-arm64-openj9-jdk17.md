---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 11:40:13 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 9 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 34-49 cores)</summary>

```
1795192440 34
1795192445 34
1795192450 34
1795192455 34
1795192460 34
1795192465 34
1795192470 34
1795192475 34
1795192480 34
1795192485 34
1795192490 34
1795192495 34
1795192500 49
1795192505 49
1795192510 49
1795192515 49
1795192520 49
1795192525 49
1795192530 49
1795192535 49
```
</details>

---

