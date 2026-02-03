---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 08:20:47 EST

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 10-33 cores)</summary>

```
1770124539 10
1770124544 10
1770124549 10
1770124554 10
1770124559 10
1770124564 10
1770124569 10
1770124574 10
1770124579 10
1770124584 10
1770124589 10
1770124594 10
1770124599 10
1770124604 33
1770124609 33
1770124614 33
1770124619 33
1770124624 33
1770124629 33
1770124634 33
```
</details>

---

