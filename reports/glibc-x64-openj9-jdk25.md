---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 10:08:38 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
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
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (7 unique values: 62-71 cores)</summary>

```
1790172174 66
1790172179 66
1790172184 68
1790172189 68
1790172194 68
1790172199 68
1790172204 68
1790172209 68
1790172214 69
1790172219 69
1790172224 69
1790172229 69
1790172234 69
1790172239 69
1790172244 69
1790172249 71
1790172254 71
1790172259 71
1790172264 71
1790172269 70
```
</details>

---

