---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 08:09:20 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 14 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795525404 64
1795525409 64
1795525414 64
1795525419 64
1795525424 64
1795525429 64
1795525434 64
1795525439 64
1795525444 64
1795525449 64
1795525454 64
1795525459 64
1795525464 64
1795525469 64
1795525474 64
1795525479 64
1795525484 64
1795525489 64
1795525494 64
1795525499 64
```
</details>

---

