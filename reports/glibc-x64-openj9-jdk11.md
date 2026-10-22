---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 12:29:05 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792686124 32
1792686129 32
1792686134 32
1792686139 32
1792686144 32
1792686149 30
1792686154 30
1792686159 30
1792686164 30
1792686169 30
1792686174 30
1792686179 30
1792686184 30
1792686189 30
1792686194 30
1792686199 30
1792686204 30
1792686209 30
1792686214 30
1792686219 30
```
</details>

---

