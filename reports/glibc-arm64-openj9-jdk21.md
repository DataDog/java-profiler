---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 05:14:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 33-50 cores)</summary>

```
1795169294 38
1795169299 38
1795169304 38
1795169309 38
1795169314 38
1795169319 38
1795169324 38
1795169329 33
1795169334 33
1795169339 33
1795169344 33
1795169349 33
1795169354 33
1795169359 33
1795169364 33
1795169369 33
1795169374 33
1795169379 33
1795169384 33
1795169389 50
```
</details>

---

