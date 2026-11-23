---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 06:57:00 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 76-84 cores)</summary>

```
1795434709 84
1795434714 84
1795434720 84
1795434725 84
1795434730 84
1795434735 84
1795434740 84
1795434745 84
1795434750 84
1795434755 84
1795434760 84
1795434765 76
1795434770 76
1795434775 76
1795434780 79
1795434785 79
1795434790 79
1795434795 79
1795434800 79
1795434805 79
```
</details>

---

