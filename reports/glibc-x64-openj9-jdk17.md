---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 09:48:42 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (4 unique values: 59-62 cores)</summary>

```
1790171063 62
1790171068 59
1790171073 59
1790171078 59
1790171083 59
1790171088 61
1790171093 61
1790171098 61
1790171103 61
1790171108 61
1790171113 61
1790171118 61
1790171123 59
1790171128 59
1790171133 60
1790171138 60
1790171143 60
1790171148 60
1790171153 60
1790171158 62
```
</details>

---

