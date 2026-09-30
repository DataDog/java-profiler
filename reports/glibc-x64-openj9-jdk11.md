---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 06:19:11 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 938 |
| Sample Rate | 15.63/sec |
| Health Score | 977% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1790763301 85
1790763306 85
1790763311 85
1790763316 85
1790763321 85
1790763326 85
1790763331 83
1790763336 83
1790763341 83
1790763346 83
1790763351 83
1790763356 83
1790763361 85
1790763366 85
1790763371 85
1790763376 85
1790763381 85
1790763386 85
1790763391 85
1790763396 85
```
</details>

---

