---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-02 12:03:39 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 854 |
| Sample Rate | 14.23/sec |
| Health Score | 889% |
| Threads | 12 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770051355 27
1770051360 27
1770051365 27
1770051370 27
1770051375 27
1770051380 27
1770051385 27
1770051390 27
1770051395 27
1770051400 27
1770051405 27
1770051410 27
1770051415 32
1770051420 32
1770051425 32
1770051430 32
1770051435 32
1770051440 32
1770051445 32
1770051450 32
```
</details>

---

