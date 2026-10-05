---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-05 13:24:32 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 808 |
| Sample Rate | 13.47/sec |
| Health Score | 842% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791220765 43
1791220770 43
1791220775 43
1791220780 43
1791220785 43
1791220790 43
1791220795 43
1791220800 43
1791220805 43
1791220810 43
1791220815 48
1791220820 48
1791220825 48
1791220830 48
1791220835 48
1791220840 48
1791220845 48
1791220850 48
1791220855 48
1791220860 48
```
</details>

---

