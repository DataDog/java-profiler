---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-03 07:41:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793709426 48
1793709431 48
1793709436 48
1793709441 48
1793709446 48
1793709451 48
1793709456 48
1793709461 48
1793709466 48
1793709471 48
1793709476 48
1793709482 48
1793709487 48
1793709492 48
1793709497 48
1793709502 48
1793709507 48
1793709512 48
1793709517 48
1793709522 48
```
</details>

---

