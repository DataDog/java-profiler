---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 08:27:59 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (5 unique values: 36-67 cores)</summary>

```
1776687623 38
1776687628 38
1776687633 38
1776687638 38
1776687643 38
1776687648 38
1776687653 38
1776687658 38
1776687663 40
1776687668 40
1776687673 36
1776687678 36
1776687683 38
1776687688 38
1776687693 36
1776687698 36
1776687703 36
1776687708 36
1776687713 40
1776687718 40
```
</details>

---

