---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 09:00:16 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 40-76 cores)</summary>

```
1778158380 41
1778158385 41
1778158390 41
1778158395 40
1778158400 40
1778158405 40
1778158410 40
1778158415 40
1778158420 40
1778158425 40
1778158430 40
1778158435 40
1778158440 40
1778158445 40
1778158450 40
1778158455 40
1778158460 40
1778158465 74
1778158470 74
1778158475 74
```
</details>

---

