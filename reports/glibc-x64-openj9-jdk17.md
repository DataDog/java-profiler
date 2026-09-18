---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 03:39:52 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (7 unique values: 72-96 cores)</summary>

```
1789716546 90
1789716551 90
1789716556 92
1789716561 92
1789716566 92
1789716571 96
1789716576 96
1789716581 96
1789716586 94
1789716591 94
1789716596 94
1789716601 92
1789716606 92
1789716611 92
1789716616 92
1789716621 92
1789716626 92
1789716631 92
1789716636 72
1789716641 72
```
</details>

---

