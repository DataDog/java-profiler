---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:39:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795196124 50
1795196129 50
1795196134 50
1795196139 50
1795196144 50
1795196149 50
1795196154 50
1795196159 50
1795196164 50
1795196169 50
1795196174 50
1795196179 50
1795196184 50
1795196189 50
1795196194 50
1795196199 50
1795196204 50
1795196209 50
1795196214 50
1795196219 50
```
</details>

---

