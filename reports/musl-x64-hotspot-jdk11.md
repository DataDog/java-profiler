---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 09:57:59 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 40-75 cores)</summary>

```
1789998720 67
1789998725 67
1789998730 67
1789998735 67
1789998740 75
1789998745 75
1789998750 75
1789998755 75
1789998760 75
1789998765 75
1789998770 75
1789998775 75
1789998780 75
1789998785 75
1789998790 40
1789998795 40
1789998800 40
1789998805 40
1789998810 40
1789998815 40
```
</details>

---

