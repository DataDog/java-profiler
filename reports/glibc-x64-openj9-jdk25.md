---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 05:59:00 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 65-86 cores)</summary>

```
1794912856 73
1794912861 73
1794912866 73
1794912871 73
1794912876 73
1794912881 75
1794912886 75
1794912891 73
1794912896 73
1794912901 73
1794912906 73
1794912911 73
1794912916 73
1794912921 73
1794912926 73
1794912931 73
1794912936 73
1794912941 65
1794912946 65
1794912951 65
```
</details>

---

