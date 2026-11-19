---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:28:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 15 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 48-64 cores)</summary>

```
1795108873 48
1795108878 48
1795108883 48
1795108888 48
1795108893 50
1795108898 50
1795108903 64
1795108908 64
1795108913 64
1795108918 64
1795108923 64
1795108928 64
1795108933 64
1795108938 64
1795108943 64
1795108948 64
1795108953 64
1795108958 64
1795108963 64
1795108968 64
```
</details>

---

