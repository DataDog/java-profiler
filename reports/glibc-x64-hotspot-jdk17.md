---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-08 14:27:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (5 unique values: 47-66 cores)</summary>

```
1794165838 62
1794165843 62
1794165848 62
1794165853 64
1794165858 64
1794165863 64
1794165868 64
1794165873 64
1794165878 64
1794165883 64
1794165888 64
1794165893 66
1794165898 66
1794165903 66
1794165908 66
1794165913 49
1794165918 49
1794165923 49
1794165928 49
1794165933 49
```
</details>

---

