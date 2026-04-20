---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 10:34:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776695074 59
1776695079 59
1776695084 59
1776695089 59
1776695094 59
1776695099 59
1776695104 59
1776695109 59
1776695114 59
1776695119 59
1776695124 59
1776695129 59
1776695134 59
1776695139 59
1776695144 59
1776695149 59
1776695154 59
1776695159 59
1776695164 64
1776695169 64
```
</details>

---

