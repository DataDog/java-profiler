---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 13:55:19 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (4 unique values: 43-64 cores)</summary>

```
1795027809 43
1795027814 43
1795027819 43
1795027824 56
1795027829 56
1795027834 56
1795027839 56
1795027844 56
1795027849 56
1795027854 56
1795027859 56
1795027864 56
1795027869 56
1795027874 56
1795027879 56
1795027884 59
1795027889 59
1795027894 59
1795027899 64
1795027904 64
```
</details>

---

