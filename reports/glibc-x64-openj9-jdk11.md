---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:21:11 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 72-87 cores)</summary>

```
1795195012 72
1795195017 72
1795195022 72
1795195027 72
1795195032 72
1795195037 72
1795195042 72
1795195047 72
1795195052 72
1795195057 72
1795195062 72
1795195067 87
1795195072 87
1795195077 87
1795195083 87
1795195088 87
1795195093 87
1795195098 87
1795195103 87
1795195108 87
```
</details>

---

