---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-08 10:54:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1791470915 48
1791470920 48
1791470925 48
1791470930 48
1791470935 40
1791470940 40
1791470945 40
1791470950 40
1791470955 40
1791470960 40
1791470965 40
1791470970 36
1791470975 36
1791470980 36
1791470985 36
1791470990 36
1791470995 36
1791471000 36
1791471005 36
1791471010 36
```
</details>

---

