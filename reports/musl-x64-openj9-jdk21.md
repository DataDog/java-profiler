---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 12:29:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 11 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1792686144 43
1792686149 43
1792686154 43
1792686159 43
1792686164 43
1792686169 43
1792686174 43
1792686179 43
1792686184 43
1792686189 43
1792686194 43
1792686199 43
1792686204 41
1792686209 41
1792686214 41
1792686219 41
1792686224 41
1792686229 41
1792686234 41
1792686239 41
```
</details>

---

