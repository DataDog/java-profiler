---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-23 10:04:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (8 unique values: 70-80 cores)</summary>

```
1776952757 80
1776952762 80
1776952767 80
1776952772 80
1776952777 78
1776952782 78
1776952787 78
1776952792 75
1776952797 75
1776952802 73
1776952807 73
1776952812 73
1776952817 72
1776952822 72
1776952827 72
1776952832 71
1776952837 71
1776952842 71
1776952847 71
1776952852 71
```
</details>

---

