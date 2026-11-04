---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 12:28:14 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1793812775 89
1793812780 89
1793812785 89
1793812790 89
1793812795 89
1793812800 89
1793812805 89
1793812810 89
1793812815 89
1793812820 89
1793812825 89
1793812830 89
1793812835 89
1793812840 89
1793812845 89
1793812850 89
1793812855 89
1793812860 89
1793812865 89
1793812870 91
```
</details>

---

