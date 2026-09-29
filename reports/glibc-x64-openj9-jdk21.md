---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 05:18:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 12 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 85-96 cores)</summary>

```
1790673298 96
1790673303 96
1790673308 96
1790673313 96
1790673318 96
1790673323 96
1790673328 96
1790673333 96
1790673338 85
1790673343 85
1790673348 85
1790673353 85
1790673358 85
1790673363 85
1790673368 85
1790673373 85
1790673378 85
1790673383 85
1790673388 85
1790673393 85
```
</details>

---

