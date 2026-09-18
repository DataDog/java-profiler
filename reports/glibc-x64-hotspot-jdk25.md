---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:13:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 78-80 cores)</summary>

```
1789743439 78
1789743444 78
1789743449 78
1789743454 78
1789743459 78
1789743464 78
1789743469 80
1789743474 80
1789743479 80
1789743484 80
1789743489 80
1789743494 80
1789743499 80
1789743504 80
1789743509 78
1789743514 78
1789743519 78
1789743524 78
1789743529 78
1789743534 78
```
</details>

---

