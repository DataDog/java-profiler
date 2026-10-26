---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 06:57:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 789 |
| Sample Rate | 13.15/sec |
| Health Score | 822% |
| Threads | 12 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 72-78 cores)</summary>

```
1793012003 72
1793012008 72
1793012013 72
1793012018 74
1793012023 74
1793012028 72
1793012033 72
1793012038 72
1793012043 72
1793012048 72
1793012053 72
1793012058 72
1793012063 72
1793012068 72
1793012073 72
1793012078 72
1793012083 74
1793012088 74
1793012093 78
1793012098 78
```
</details>

---

