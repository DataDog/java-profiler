---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 04:45:05 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 933 |
| Sample Rate | 15.55/sec |
| Health Score | 972% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 66-70 cores)</summary>

```
1789979983 66
1789979988 66
1789979993 66
1789979998 66
1789980003 66
1789980008 68
1789980013 68
1789980018 68
1789980023 70
1789980028 70
1789980033 70
1789980038 70
1789980043 70
1789980048 70
1789980053 70
1789980058 70
1789980063 70
1789980068 70
1789980073 70
1789980078 70
```
</details>

---

