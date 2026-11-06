---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-06 15:13:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793995759 48
1793995764 48
1793995769 48
1793995775 48
1793995780 48
1793995785 48
1793995790 48
1793995795 48
1793995800 48
1793995805 48
1793995810 48
1793995815 48
1793995820 48
1793995825 48
1793995830 48
1793995835 48
1793995840 48
1793995845 48
1793995850 48
1793995855 48
```
</details>

---

