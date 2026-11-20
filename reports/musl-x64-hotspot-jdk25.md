---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 05:56:28 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 429 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 11 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 64-67 cores)</summary>

```
1795171806 67
1795171811 67
1795171816 67
1795171821 67
1795171826 67
1795171831 67
1795171836 67
1795171841 67
1795171846 67
1795171851 67
1795171856 64
1795171861 64
1795171866 64
1795171871 64
1795171876 64
1795171881 64
1795171886 64
1795171891 64
1795171896 64
1795171901 64
```
</details>

---

