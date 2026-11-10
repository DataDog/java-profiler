---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 09:09:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 297 |
| Sample Rate | 4.95/sec |
| Health Score | 309% |
| Threads | 13 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794319437 51
1794319442 51
1794319447 51
1794319452 51
1794319457 51
1794319462 51
1794319467 51
1794319472 51
1794319477 51
1794319482 51
1794319487 64
1794319492 64
1794319497 64
1794319502 51
1794319507 51
1794319512 51
1794319517 51
1794319522 51
1794319527 51
1794319532 51
```
</details>

---

