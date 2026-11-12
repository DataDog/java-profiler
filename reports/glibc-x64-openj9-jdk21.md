---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 07:47:07 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 69-94 cores)</summary>

```
1794487352 94
1794487357 92
1794487362 92
1794487367 92
1794487372 92
1794487377 94
1794487382 94
1794487387 94
1794487392 94
1794487397 92
1794487402 92
1794487407 92
1794487412 92
1794487417 92
1794487422 92
1794487427 92
1794487432 92
1794487437 69
1794487442 69
1794487447 69
```
</details>

---

