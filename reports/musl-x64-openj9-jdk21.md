---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-23 10:22:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 9 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (4 unique values: 17-24 cores)</summary>

```
1776953762 24
1776953767 24
1776953772 24
1776953777 24
1776953782 24
1776953787 24
1776953792 24
1776953797 24
1776953802 21
1776953807 21
1776953812 21
1776953817 21
1776953822 21
1776953827 21
1776953832 19
1776953837 19
1776953842 19
1776953847 19
1776953852 19
1776953857 19
```
</details>

---

