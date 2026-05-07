---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 11:01:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 958 |
| Sample Rate | 15.97/sec |
| Health Score | 998% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 69-75 cores)</summary>

```
1778165843 71
1778165848 71
1778165853 69
1778165858 69
1778165863 69
1778165868 69
1778165873 69
1778165878 69
1778165883 73
1778165888 73
1778165893 73
1778165898 73
1778165903 73
1778165908 73
1778165913 73
1778165918 75
1778165923 75
1778165928 75
1778165933 75
1778165938 75
```
</details>

---

