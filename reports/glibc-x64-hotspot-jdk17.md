---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:03:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 42-96 cores)</summary>

```
1789743465 42
1789743470 42
1789743475 42
1789743480 66
1789743485 66
1789743490 66
1789743495 66
1789743500 66
1789743505 66
1789743510 66
1789743515 66
1789743520 66
1789743525 66
1789743530 66
1789743535 66
1789743540 96
1789743545 96
1789743551 57
1789743556 57
1789743561 57
```
</details>

---

