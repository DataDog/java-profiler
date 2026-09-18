---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 04:34:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 12 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 48-50 cores)</summary>

```
1789719892 48
1789719897 48
1789719902 48
1789719907 50
1789719912 50
1789719917 50
1789719922 50
1789719927 50
1789719932 50
1789719937 50
1789719942 50
1789719948 50
1789719953 50
1789719958 50
1789719963 50
1789719968 50
1789719973 50
1789719978 50
1789719983 50
1789719988 50
```
</details>

---

