---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-17 11:46:56 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1776440634 32
1776440639 32
1776440644 32
1776440649 27
1776440654 27
1776440659 27
1776440664 27
1776440669 27
1776440674 27
1776440679 27
1776440684 27
1776440689 27
1776440694 27
1776440699 27
1776440704 27
1776440709 27
1776440714 27
1776440719 27
1776440724 27
1776440729 27
```
</details>

---

