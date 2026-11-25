---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:01:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 189 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 14 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795625826 33
1795625831 33
1795625836 33
1795625841 33
1795625846 33
1795625851 33
1795625856 33
1795625861 33
1795625866 33
1795625871 33
1795625876 33
1795625881 33
1795625886 33
1795625891 33
1795625896 33
1795625901 33
1795625906 33
1795625911 33
1795625916 33
1795625921 33
```
</details>

---

