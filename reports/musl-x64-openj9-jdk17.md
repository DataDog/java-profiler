---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-02 12:03:39 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1770051350 23
1770051355 23
1770051360 23
1770051365 23
1770051370 23
1770051375 23
1770051380 23
1770051385 23
1770051390 23
1770051395 23
1770051400 23
1770051405 23
1770051410 23
1770051415 23
1770051420 23
1770051425 23
1770051430 23
1770051435 28
1770051440 28
1770051445 28
```
</details>

---

