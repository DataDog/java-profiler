---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 15:35:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 53-76 cores)</summary>

```
1789673370 76
1789673375 76
1789673380 76
1789673385 76
1789673390 76
1789673395 76
1789673400 76
1789673405 76
1789673410 76
1789673415 76
1789673420 76
1789673425 76
1789673430 76
1789673435 76
1789673440 53
1789673445 53
1789673450 53
1789673455 53
1789673460 53
1789673465 53
```
</details>

---

