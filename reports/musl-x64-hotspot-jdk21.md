---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 11:41:38 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 72-75 cores)</summary>

```
1776699082 74
1776699087 74
1776699092 74
1776699097 75
1776699102 75
1776699107 75
1776699112 75
1776699117 75
1776699122 72
1776699127 72
1776699132 72
1776699137 72
1776699142 72
1776699147 72
1776699152 72
1776699157 72
1776699162 72
1776699167 72
1776699172 72
1776699177 72
```
</details>

---

