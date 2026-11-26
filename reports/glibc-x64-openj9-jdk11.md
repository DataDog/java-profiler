---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:18:49 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 75-80 cores)</summary>

```
1795706083 80
1795706088 80
1795706093 80
1795706098 80
1795706103 80
1795706108 80
1795706113 80
1795706118 80
1795706123 80
1795706128 80
1795706133 80
1795706138 80
1795706143 80
1795706148 80
1795706153 75
1795706159 75
1795706164 75
1795706169 75
1795706174 75
1795706179 75
```
</details>

---

