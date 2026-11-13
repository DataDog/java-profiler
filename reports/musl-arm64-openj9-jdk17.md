---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 06:08:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 9 |
| Allocations | 141 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 12 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (4 unique values: 36-43 cores)</summary>

```
1794567791 41
1794567796 41
1794567801 41
1794567806 41
1794567811 41
1794567816 41
1794567821 41
1794567826 41
1794567831 41
1794567836 36
1794567841 36
1794567846 36
1794567851 36
1794567856 38
1794567861 38
1794567866 38
1794567871 38
1794567876 43
1794567881 43
1794567886 43
```
</details>

---

