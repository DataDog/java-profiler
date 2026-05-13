---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-13 09:58:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1000 |
| Sample Rate | 16.67/sec |
| Health Score | 1042% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 65-70 cores)</summary>

```
1778680369 65
1778680374 65
1778680379 65
1778680384 70
1778680389 70
1778680394 70
1778680399 70
1778680404 68
1778680409 68
1778680414 68
1778680419 68
1778680424 68
1778680429 65
1778680434 65
1778680439 65
1778680444 67
1778680449 67
1778680454 67
1778680459 67
1778680464 67
```
</details>

---

