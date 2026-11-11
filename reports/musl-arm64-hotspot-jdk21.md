---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 16:06:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 14 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1794430816 34
1794430821 34
1794430826 34
1794430831 39
1794430836 39
1794430841 39
1794430846 39
1794430851 39
1794430856 39
1794430861 39
1794430866 39
1794430871 39
1794430877 39
1794430882 39
1794430887 39
1794430892 39
1794430897 39
1794430902 39
1794430907 39
1794430912 39
```
</details>

---

