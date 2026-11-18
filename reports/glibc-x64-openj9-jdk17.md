---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:33:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (6 unique values: 74-93 cores)</summary>

```
1795011962 84
1795011967 84
1795011972 93
1795011977 93
1795011982 93
1795011987 93
1795011992 93
1795011997 93
1795012002 93
1795012007 90
1795012012 90
1795012017 84
1795012022 84
1795012027 84
1795012032 81
1795012037 81
1795012042 81
1795012047 81
1795012052 81
1795012057 81
```
</details>

---

