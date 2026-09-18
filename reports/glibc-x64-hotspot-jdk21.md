---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 02:28:25 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 53-61 cores)</summary>

```
1789712683 57
1789712688 57
1789712693 59
1789712698 59
1789712703 59
1789712708 59
1789712713 59
1789712718 59
1789712723 59
1789712728 59
1789712733 61
1789712738 61
1789712743 61
1789712749 61
1789712754 61
1789712759 61
1789712764 61
1789712769 61
1789712774 61
1789712779 61
```
</details>

---

