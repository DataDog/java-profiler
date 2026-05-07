---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 06:54:36 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1033 |
| Sample Rate | 17.22/sec |
| Health Score | 1076% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (5 unique values: 78-91 cores)</summary>

```
1778151047 91
1778151052 86
1778151057 86
1778151062 86
1778151067 86
1778151072 86
1778151077 79
1778151082 79
1778151087 79
1778151092 79
1778151097 81
1778151102 81
1778151107 81
1778151112 81
1778151117 81
1778151122 81
1778151127 81
1778151132 78
1778151137 78
1778151142 78
```
</details>

---

