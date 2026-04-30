---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-30 06:13:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (3 unique values: 63-72 cores)</summary>

```
1777543704 63
1777543709 63
1777543714 63
1777543719 63
1777543724 63
1777543729 63
1777543734 67
1777543739 67
1777543744 67
1777543749 67
1777543754 67
1777543759 67
1777543764 67
1777543769 67
1777543774 67
1777543779 67
1777543784 67
1777543789 67
1777543794 67
1777543799 67
```
</details>

---

