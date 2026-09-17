---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 15:41:05 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789673465 38
1789673470 38
1789673475 38
1789673480 38
1789673485 38
1789673490 38
1789673495 38
1789673500 38
1789673505 38
1789673510 48
1789673515 48
1789673520 48
1789673525 48
1789673530 48
1789673535 48
1789673540 48
1789673545 48
1789673550 48
1789673555 48
1789673560 43
```
</details>

---

