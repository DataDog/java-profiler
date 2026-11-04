---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-03 20:28:24 EST

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 8 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 15-32 cores)</summary>

```
1793755426 15
1793755431 15
1793755436 15
1793755441 15
1793755446 15
1793755451 15
1793755456 15
1793755461 15
1793755466 15
1793755471 15
1793755476 32
1793755481 32
1793755486 32
1793755491 32
1793755496 32
1793755501 32
1793755506 32
1793755511 32
1793755516 32
1793755521 32
```
</details>

---

