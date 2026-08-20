---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-20 08:51:02 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 9 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1787229957 16
1787229962 16
1787229967 16
1787229972 16
1787229977 16
1787229982 16
1787229987 16
1787229992 16
1787229997 16
1787230002 16
1787230007 16
1787230013 16
1787230018 16
1787230023 16
1787230028 16
1787230033 16
1787230038 16
1787230043 16
1787230048 16
1787230053 16
```
</details>

---

