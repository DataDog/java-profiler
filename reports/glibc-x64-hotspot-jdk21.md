---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 19:15:39 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 60-96 cores)</summary>

```
1789686673 94
1789686678 94
1789686683 94
1789686688 94
1789686693 94
1789686698 94
1789686703 94
1789686708 94
1789686713 94
1789686718 94
1789686723 96
1789686728 96
1789686733 96
1789686738 96
1789686743 96
1789686748 96
1789686753 96
1789686758 96
1789686763 96
1789686768 96
```
</details>

---

