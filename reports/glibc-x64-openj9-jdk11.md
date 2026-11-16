---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 13:04:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 966 |
| Sample Rate | 16.10/sec |
| Health Score | 1006% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 74-79 cores)</summary>

```
1794851913 79
1794851918 79
1794851923 74
1794851928 74
1794851933 74
1794851938 74
1794851943 74
1794851948 74
1794851953 74
1794851958 74
1794851963 74
1794851968 76
1794851973 76
1794851978 76
1794851983 76
1794851988 76
1794851993 76
1794851998 76
1794852003 76
1794852008 76
```
</details>

---

