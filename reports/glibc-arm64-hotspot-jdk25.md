---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-23 10:04:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776952727 64
1776952732 64
1776952737 64
1776952742 64
1776952747 64
1776952752 64
1776952757 64
1776952762 64
1776952767 64
1776952772 64
1776952777 64
1776952782 64
1776952787 64
1776952792 64
1776952797 64
1776952802 64
1776952807 64
1776952812 64
1776952817 64
1776952822 64
```
</details>

---

