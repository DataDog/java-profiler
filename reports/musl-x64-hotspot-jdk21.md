---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-09 05:44:49 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 50-75 cores)</summary>

```
1791538770 75
1791538775 75
1791538780 75
1791538785 75
1791538790 75
1791538795 75
1791538800 75
1791538805 75
1791538810 75
1791538815 52
1791538820 52
1791538825 52
1791538830 52
1791538835 52
1791538840 52
1791538845 52
1791538850 52
1791538855 52
1791538860 50
1791538865 50
```
</details>

---

