---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-23 10:30:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (5 unique values: 82-96 cores)</summary>

```
1792765603 82
1792765608 82
1792765613 82
1792765618 82
1792765623 82
1792765628 82
1792765633 82
1792765638 82
1792765643 82
1792765648 84
1792765653 84
1792765658 84
1792765663 84
1792765668 84
1792765673 84
1792765678 84
1792765683 84
1792765688 84
1792765693 86
1792765698 86
```
</details>

---

