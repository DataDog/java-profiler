---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-22 11:31:59 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (5 unique values: 30-65 cores)</summary>

```
1776871143 30
1776871148 30
1776871153 65
1776871158 65
1776871163 60
1776871168 60
1776871173 60
1776871178 60
1776871183 60
1776871188 60
1776871193 60
1776871198 60
1776871203 55
1776871208 55
1776871213 55
1776871218 55
1776871223 55
1776871228 55
1776871233 55
1776871238 55
```
</details>

---

