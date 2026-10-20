---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 17:39:40 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 313 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1001 |
| Sample Rate | 16.68/sec |
| Health Score | 1042% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1792532086 91
1792532091 91
1792532096 91
1792532101 91
1792532107 91
1792532112 91
1792532117 91
1792532122 91
1792532127 89
1792532132 89
1792532137 89
1792532142 89
1792532147 89
1792532153 89
1792532158 89
1792532163 89
1792532168 89
1792532173 89
1792532178 89
1792532183 89
```
</details>

---

