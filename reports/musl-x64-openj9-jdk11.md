---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:10:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 10 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (2 unique values: 57-59 cores)</summary>

```
1789743427 59
1789743432 59
1789743437 59
1789743442 59
1789743447 59
1789743452 59
1789743457 59
1789743462 59
1789743467 59
1789743472 59
1789743477 59
1789743482 57
1789743487 57
1789743492 57
1789743497 57
1789743502 57
1789743507 57
1789743512 57
1789743517 57
1789743522 57
```
</details>

---

