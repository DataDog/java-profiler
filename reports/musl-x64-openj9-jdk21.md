---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 06:22:08 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770117424 32
1770117429 32
1770117434 32
1770117439 32
1770117444 32
1770117449 32
1770117454 32
1770117459 32
1770117464 32
1770117469 32
1770117474 32
1770117479 32
1770117484 32
1770117489 32
1770117494 32
1770117499 32
1770117504 32
1770117509 32
1770117514 32
1770117519 32
```
</details>

---

