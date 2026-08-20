---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-20 09:32:07 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787232432 94
1787232437 94
1787232442 94
1787232447 94
1787232452 94
1787232457 94
1787232462 94
1787232467 94
1787232472 94
1787232477 94
1787232482 94
1787232487 96
1787232492 96
1787232497 96
1787232502 96
1787232507 96
1787232512 96
1787232517 96
1787232522 96
1787232527 96
```
</details>

---

