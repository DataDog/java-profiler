---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 16:06:29 EST

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
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 13 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794430806 48
1794430811 48
1794430816 48
1794430821 48
1794430826 48
1794430831 48
1794430836 48
1794430841 48
1794430846 48
1794430851 48
1794430856 48
1794430861 48
1794430866 48
1794430871 43
1794430876 43
1794430881 43
1794430886 43
1794430891 43
1794430896 43
1794430901 43
```
</details>

---

