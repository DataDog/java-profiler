---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 08:52:58 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 12 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795614485 64
1795614490 64
1795614495 64
1795614500 64
1795614505 64
1795614510 64
1795614515 64
1795614520 64
1795614525 64
1795614530 64
1795614535 64
1795614540 64
1795614545 64
1795614550 64
1795614555 64
1795614560 64
1795614565 64
1795614570 64
1795614575 64
1795614580 64
```
</details>

---

