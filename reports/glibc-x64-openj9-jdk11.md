---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:28:55 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1031 |
| Sample Rate | 17.18/sec |
| Health Score | 1074% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 38-45 cores)</summary>

```
1789719938 38
1789719943 38
1789719948 38
1789719953 38
1789719958 38
1789719963 38
1789719968 40
1789719973 40
1789719978 40
1789719983 40
1789719988 40
1789719993 40
1789719998 40
1789720003 40
1789720008 40
1789720013 38
1789720018 38
1789720023 38
1789720028 38
1789720033 38
```
</details>

---

