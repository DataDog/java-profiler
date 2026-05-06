---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 14:08:09 EDT

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 867 |
| Sample Rate | 14.45/sec |
| Health Score | 903% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (5 unique values: 25-36 cores)</summary>

```
1778090390 33
1778090395 33
1778090400 33
1778090405 33
1778090410 33
1778090415 33
1778090420 33
1778090425 36
1778090430 36
1778090435 31
1778090440 31
1778090445 31
1778090450 31
1778090455 31
1778090460 31
1778090465 31
1778090470 30
1778090475 30
1778090480 30
1778090485 30
```
</details>

---

