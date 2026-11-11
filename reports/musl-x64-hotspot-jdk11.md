---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 16:06:31 EST

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 8 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 875 |
| Sample Rate | 14.58/sec |
| Health Score | 911% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 91-93 cores)</summary>

```
1794430801 93
1794430806 93
1794430811 93
1794430816 93
1794430821 93
1794430826 93
1794430831 93
1794430836 93
1794430841 93
1794430846 93
1794430852 93
1794430857 93
1794430862 93
1794430867 93
1794430872 93
1794430877 91
1794430882 91
1794430887 91
1794430892 91
1794430897 91
```
</details>

---

