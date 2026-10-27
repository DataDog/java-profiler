---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 19:15:11 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1793142548 94
1793142553 94
1793142558 94
1793142563 94
1793142568 94
1793142573 94
1793142578 94
1793142583 94
1793142588 94
1793142593 94
1793142598 94
1793142603 96
1793142608 96
1793142613 96
1793142618 96
1793142623 96
1793142628 96
1793142633 96
1793142638 96
1793142643 96
```
</details>

---

