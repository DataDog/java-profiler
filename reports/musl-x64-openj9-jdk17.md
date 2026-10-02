---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-02 05:51:53 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 901 |
| Sample Rate | 15.02/sec |
| Health Score | 939% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (5 unique values: 50-55 cores)</summary>

```
1790934400 51
1790934405 51
1790934410 51
1790934415 55
1790934420 55
1790934425 55
1790934430 55
1790934435 55
1790934440 55
1790934445 55
1790934450 52
1790934455 52
1790934460 52
1790934465 52
1790934470 52
1790934475 52
1790934480 52
1790934485 52
1790934490 50
1790934495 50
```
</details>

---

