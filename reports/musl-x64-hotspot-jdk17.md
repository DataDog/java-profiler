---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-14 18:05:38 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1065 |
| Sample Rate | 17.75/sec |
| Health Score | 1109% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 65-74 cores)</summary>

```
1776204084 74
1776204089 74
1776204094 74
1776204099 74
1776204104 74
1776204109 74
1776204114 74
1776204119 74
1776204124 74
1776204129 69
1776204134 69
1776204139 69
1776204144 69
1776204149 69
1776204154 69
1776204159 69
1776204164 69
1776204169 69
1776204174 69
1776204179 69
```
</details>

---

