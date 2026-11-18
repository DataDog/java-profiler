---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 13:22:12 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 819 |
| Sample Rate | 13.65/sec |
| Health Score | 853% |
| Threads | 12 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 56-69 cores)</summary>

```
1795025844 58
1795025849 56
1795025854 56
1795025859 56
1795025864 56
1795025869 56
1795025874 60
1795025879 60
1795025884 60
1795025889 60
1795025894 60
1795025899 60
1795025904 60
1795025909 60
1795025914 60
1795025919 60
1795025924 69
1795025929 69
1795025934 69
1795025939 69
```
</details>

---

