---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:25:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 13 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794572433 51
1794572438 51
1794572443 51
1794572448 51
1794572453 51
1794572458 51
1794572463 51
1794572468 51
1794572473 51
1794572478 51
1794572483 51
1794572488 51
1794572493 51
1794572498 51
1794572503 51
1794572508 51
1794572513 51
1794572518 51
1794572523 51
1794572528 51
```
</details>

---

