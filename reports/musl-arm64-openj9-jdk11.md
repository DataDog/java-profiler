---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-01 09:14:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1777640892 38
1777640897 38
1777640902 38
1777640907 38
1777640912 38
1777640917 38
1777640922 38
1777640927 38
1777640932 38
1777640937 38
1777640942 43
1777640947 43
1777640952 43
1777640957 43
1777640962 43
1777640967 43
1777640972 48
1777640977 48
1777640982 48
1777640987 48
```
</details>

---

