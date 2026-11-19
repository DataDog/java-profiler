---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:28:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (3 unique values: 63-70 cores)</summary>

```
1795108883 70
1795108888 70
1795108893 70
1795108898 70
1795108903 70
1795108908 70
1795108913 70
1795108918 70
1795108923 70
1795108928 70
1795108933 70
1795108938 65
1795108943 65
1795108948 65
1795108953 65
1795108958 65
1795108963 65
1795108968 65
1795108973 65
1795108978 63
```
</details>

---

