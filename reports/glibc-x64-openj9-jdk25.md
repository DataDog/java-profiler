---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 10:44:06 EDT

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
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 9 |
| Allocations | 440 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 73-83 cores)</summary>

```
1790779114 73
1790779119 73
1790779124 73
1790779129 73
1790779134 73
1790779139 75
1790779144 75
1790779149 75
1790779154 75
1790779159 75
1790779164 75
1790779169 75
1790779174 75
1790779179 75
1790779184 75
1790779189 75
1790779194 75
1790779199 75
1790779205 75
1790779210 75
```
</details>

---

