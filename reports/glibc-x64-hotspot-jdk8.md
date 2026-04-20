---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-20 10:20:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1776694586 48
1776694591 48
1776694596 48
1776694601 48
1776694606 48
1776694611 48
1776694616 46
1776694621 46
1776694626 46
1776694631 46
1776694636 46
1776694641 46
1776694646 46
1776694651 46
1776694656 46
1776694661 46
1776694666 46
1776694671 46
1776694676 46
1776694681 46
```
</details>

---

