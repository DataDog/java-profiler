---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-21 13:54:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 9 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776793788 64
1776793793 64
1776793798 64
1776793803 64
1776793808 64
1776793813 64
1776793818 64
1776793823 64
1776793828 64
1776793833 64
1776793838 64
1776793843 64
1776793848 64
1776793853 64
1776793858 64
1776793863 64
1776793868 64
1776793873 64
1776793878 64
1776793883 64
```
</details>

---

