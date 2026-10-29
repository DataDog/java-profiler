---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 14:13:16 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1793297248 15
1793297253 15
1793297258 15
1793297263 15
1793297268 15
1793297273 15
1793297278 15
1793297283 15
1793297288 15
1793297293 15
1793297298 15
1793297303 15
1793297308 15
1793297313 15
1793297318 15
1793297323 15
1793297328 15
1793297333 15
1793297338 15
1793297343 15
```
</details>

---

