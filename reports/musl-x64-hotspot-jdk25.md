---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-24 08:33:46 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (6 unique values: 65-92 cores)</summary>

```
1777033780 65
1777033785 65
1777033790 65
1777033795 65
1777033800 65
1777033805 65
1777033810 65
1777033815 65
1777033820 71
1777033825 71
1777033830 71
1777033835 71
1777033840 71
1777033845 71
1777033850 92
1777033855 92
1777033860 92
1777033865 92
1777033870 92
1777033875 87
```
</details>

---

