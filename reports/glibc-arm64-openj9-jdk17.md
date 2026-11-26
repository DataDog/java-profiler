---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 08:19:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 10 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 13-33 cores)</summary>

```
1795698906 13
1795698911 13
1795698916 13
1795698921 13
1795698926 13
1795698931 13
1795698936 13
1795698941 13
1795698946 13
1795698951 13
1795698956 13
1795698961 13
1795698966 13
1795698971 13
1795698976 13
1795698981 13
1795698986 13
1795698991 13
1795698996 33
1795699001 33
```
</details>

---

