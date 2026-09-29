---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 08:24:20 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 11 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (3 unique values: 85-96 cores)</summary>

```
1790684418 85
1790684423 85
1790684428 85
1790684433 85
1790684438 85
1790684443 85
1790684448 96
1790684453 96
1790684458 96
1790684463 96
1790684468 96
1790684473 96
1790684478 96
1790684483 96
1790684488 96
1790684493 96
1790684498 96
1790684503 96
1790684508 96
1790684513 96
```
</details>

---

