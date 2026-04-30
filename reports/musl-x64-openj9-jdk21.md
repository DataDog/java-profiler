---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-30 10:04:42 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1083 |
| Sample Rate | 18.05/sec |
| Health Score | 1128% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 80-88 cores)</summary>

```
1777557337 80
1777557342 80
1777557347 80
1777557352 84
1777557357 84
1777557362 84
1777557367 84
1777557372 84
1777557377 84
1777557382 84
1777557388 84
1777557393 84
1777557398 84
1777557403 84
1777557408 84
1777557413 84
1777557418 84
1777557423 84
1777557428 84
1777557433 84
```
</details>

---

