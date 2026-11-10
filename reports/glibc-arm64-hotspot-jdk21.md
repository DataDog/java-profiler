---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 13:30:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 11 |
| Allocations | 156 |

<details>
<summary>CPU Timeline (4 unique values: 38-44 cores)</summary>

```
1794334862 38
1794334867 38
1794334872 38
1794334877 38
1794334882 43
1794334887 43
1794334892 43
1794334897 39
1794334902 39
1794334907 44
1794334912 44
1794334917 44
1794334922 44
1794334927 44
1794334933 44
1794334938 44
1794334943 44
1794334948 44
1794334953 44
1794334958 44
```
</details>

---

