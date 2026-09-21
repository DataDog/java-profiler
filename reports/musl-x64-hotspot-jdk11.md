---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 03:29:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 6 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 8 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 6-32 cores)</summary>

```
1789975443 6
1789975449 6
1789975454 6
1789975459 6
1789975464 6
1789975469 6
1789975474 6
1789975479 6
1789975484 6
1789975489 6
1789975494 6
1789975499 6
1789975504 6
1789975509 32
1789975514 32
1789975519 32
1789975524 32
1789975529 32
1789975534 32
1789975539 32
```
</details>

---

