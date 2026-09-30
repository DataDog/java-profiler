---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 13:02:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1023 |
| Sample Rate | 17.05/sec |
| Health Score | 1066% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 71-74 cores)</summary>

```
1790787559 73
1790787564 73
1790787569 73
1790787574 73
1790787579 73
1790787584 73
1790787589 73
1790787594 73
1790787599 73
1790787604 73
1790787609 73
1790787614 73
1790787619 73
1790787624 73
1790787629 73
1790787634 73
1790787639 73
1790787644 71
1790787649 71
1790787654 71
```
</details>

---

