---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 06:31:39 EST

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
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794828407 43
1794828412 43
1794828417 43
1794828422 43
1794828427 48
1794828432 48
1794828437 48
1794828442 48
1794828447 48
1794828452 48
1794828457 48
1794828462 48
1794828467 48
1794828472 48
1794828477 48
1794828482 48
1794828487 48
1794828492 48
1794828497 48
1794828502 48
```
</details>

---

