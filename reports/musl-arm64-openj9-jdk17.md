---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 07:31:30 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 8 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794572834 43
1794572839 43
1794572845 43
1794572850 43
1794572855 43
1794572860 43
1794572865 48
1794572870 48
1794572875 48
1794572880 48
1794572885 48
1794572890 48
1794572895 48
1794572900 48
1794572905 48
1794572910 48
1794572915 48
1794572920 48
1794572925 48
1794572930 48
```
</details>

---

