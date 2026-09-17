---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 16:55:06 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1789678044 96
1789678049 96
1789678054 96
1789678059 94
1789678064 94
1789678069 94
1789678074 94
1789678079 94
1789678084 94
1789678089 94
1789678094 94
1789678099 94
1789678104 94
1789678109 94
1789678114 94
1789678119 94
1789678124 94
1789678129 94
1789678134 94
1789678139 94
```
</details>

---

