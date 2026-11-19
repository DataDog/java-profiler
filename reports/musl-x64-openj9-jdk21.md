---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:28:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (4 unique values: 65-77 cores)</summary>

```
1795108863 65
1795108868 65
1795108873 65
1795108878 65
1795108883 65
1795108888 65
1795108893 65
1795108898 65
1795108903 65
1795108908 73
1795108913 73
1795108918 73
1795108923 73
1795108928 73
1795108933 73
1795108938 73
1795108943 73
1795108948 73
1795108953 73
1795108958 73
```
</details>

---

