---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:27:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 11 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 90-92 cores)</summary>

```
1794572455 92
1794572460 92
1794572465 92
1794572470 92
1794572475 92
1794572480 90
1794572485 90
1794572490 90
1794572495 90
1794572500 90
1794572505 90
1794572510 92
1794572515 92
1794572520 92
1794572525 92
1794572530 92
1794572535 92
1794572540 92
1794572545 92
1794572550 92
```
</details>

---

