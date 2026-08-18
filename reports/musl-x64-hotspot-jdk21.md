---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-18 13:40:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 804 |
| Sample Rate | 13.40/sec |
| Health Score | 838% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 60-81 cores)</summary>

```
1787074516 73
1787074521 81
1787074526 81
1787074531 81
1787074536 81
1787074541 81
1787074546 81
1787074551 81
1787074556 81
1787074561 76
1787074566 76
1787074571 76
1787074576 76
1787074581 76
1787074586 76
1787074591 76
1787074596 76
1787074601 76
1787074606 76
1787074611 76
```
</details>

---

