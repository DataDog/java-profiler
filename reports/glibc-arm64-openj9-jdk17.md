---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-13 15:42:52 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 91 |

<details>
<summary>CPU Timeline (4 unique values: 50-59 cores)</summary>

```
1786649918 50
1786649923 54
1786649928 54
1786649933 54
1786649938 54
1786649943 54
1786649948 54
1786649953 54
1786649958 54
1786649963 54
1786649968 54
1786649973 54
1786649978 54
1786649983 54
1786649988 54
1786649993 54
1786649998 54
1786650003 59
1786650008 59
1786650013 53
```
</details>

---

