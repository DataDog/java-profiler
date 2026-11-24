---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 09:31:29 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 7 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 9 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1795530429 32
1795530434 32
1795530439 32
1795530444 32
1795530449 32
1795530454 32
1795530459 32
1795530465 32
1795530470 32
1795530475 32
1795530480 32
1795530485 32
1795530490 32
1795530495 32
1795530500 32
1795530505 32
1795530510 32
1795530515 32
1795530520 32
1795530525 32
```
</details>

---

