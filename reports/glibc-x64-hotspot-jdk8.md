---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-05 16:36:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 57-62 cores)</summary>

```
1791232284 62
1791232289 62
1791232294 62
1791232299 62
1791232304 62
1791232309 62
1791232314 62
1791232319 62
1791232324 62
1791232329 62
1791232334 62
1791232339 57
1791232344 57
1791232349 57
1791232354 57
1791232359 57
1791232364 57
1791232369 57
1791232374 57
1791232379 57
```
</details>

---

