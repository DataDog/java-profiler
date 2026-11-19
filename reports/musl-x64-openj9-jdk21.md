---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 08:25:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 899 |
| Sample Rate | 14.98/sec |
| Health Score | 936% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (6 unique values: 69-86 cores)</summary>

```
1795094412 81
1795094417 75
1795094422 75
1795094427 75
1795094432 80
1795094437 80
1795094442 78
1795094447 78
1795094452 78
1795094457 78
1795094462 78
1795094467 86
1795094472 86
1795094477 69
1795094482 69
1795094487 69
1795094492 69
1795094497 69
1795094502 69
1795094507 69
```
</details>

---

