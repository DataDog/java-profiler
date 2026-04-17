---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-17 10:21:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 56-60 cores)</summary>

```
1776435099 60
1776435104 60
1776435109 60
1776435114 60
1776435119 60
1776435124 60
1776435129 60
1776435134 60
1776435139 60
1776435144 60
1776435149 59
1776435154 59
1776435159 59
1776435164 59
1776435169 59
1776435174 59
1776435179 56
1776435184 56
1776435189 56
1776435194 56
```
</details>

---

