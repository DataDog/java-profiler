---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 02:28:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 902 |
| Sample Rate | 15.03/sec |
| Health Score | 939% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 34-81 cores)</summary>

```
1789712648 81
1789712653 81
1789712658 81
1789712663 81
1789712668 81
1789712673 81
1789712678 81
1789712683 81
1789712688 34
1789712693 34
1789712698 34
1789712703 34
1789712708 34
1789712713 34
1789712718 34
1789712723 34
1789712728 34
1789712733 34
1789712738 34
1789712743 34
```
</details>

---

