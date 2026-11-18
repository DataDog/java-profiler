---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:34:24 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (4 unique values: 46-51 cores)</summary>

```
1795011972 49
1795011977 51
1795011982 51
1795011987 51
1795011992 51
1795011997 51
1795012002 51
1795012007 51
1795012012 51
1795012017 51
1795012022 51
1795012027 51
1795012032 51
1795012037 48
1795012042 48
1795012047 48
1795012052 48
1795012057 48
1795012062 48
1795012067 48
```
</details>

---

