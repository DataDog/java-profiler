---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-08 14:27:50 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1794165833 24
1794165838 24
1794165843 24
1794165848 24
1794165853 24
1794165858 24
1794165863 24
1794165868 24
1794165873 24
1794165878 24
1794165883 24
1794165888 24
1794165893 24
1794165898 24
1794165903 24
1794165908 24
1794165913 29
1794165918 29
1794165923 29
1794165928 34
```
</details>

---

