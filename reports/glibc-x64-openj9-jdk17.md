---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 13:14:38 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 11 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (5 unique values: 72-87 cores)</summary>

```
1795630120 72
1795630125 72
1795630130 72
1795630135 72
1795630140 74
1795630145 74
1795630150 74
1795630155 78
1795630160 78
1795630165 78
1795630170 78
1795630175 78
1795630180 78
1795630185 78
1795630190 78
1795630195 87
1795630200 87
1795630205 85
1795630210 85
1795630215 85
```
</details>

---

