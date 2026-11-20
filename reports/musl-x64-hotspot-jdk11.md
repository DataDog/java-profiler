---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 05:56:28 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 849 |
| Sample Rate | 14.15/sec |
| Health Score | 884% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 56-60 cores)</summary>

```
1795171821 58
1795171826 58
1795171831 58
1795171836 58
1795171841 58
1795171846 58
1795171851 58
1795171856 58
1795171861 58
1795171866 58
1795171871 58
1795171876 58
1795171882 56
1795171887 56
1795171892 56
1795171897 56
1795171902 56
1795171907 56
1795171912 56
1795171917 56
```
</details>

---

