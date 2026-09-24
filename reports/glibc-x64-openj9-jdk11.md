---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 00:59:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 57-75 cores)</summary>

```
1790225628 57
1790225633 57
1790225638 57
1790225643 57
1790225648 57
1790225653 57
1790225658 57
1790225663 57
1790225668 63
1790225673 63
1790225678 63
1790225683 63
1790225688 75
1790225693 75
1790225698 75
1790225703 75
1790225708 75
1790225713 75
1790225718 75
1790225723 75
```
</details>

---

