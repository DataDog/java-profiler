---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-15 13:31:17 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1021 |
| Sample Rate | 17.02/sec |
| Health Score | 1064% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 42-52 cores)</summary>

```
1776274089 47
1776274094 47
1776274099 47
1776274104 47
1776274109 52
1776274114 52
1776274119 52
1776274124 47
1776274129 47
1776274134 47
1776274139 47
1776274144 42
1776274149 42
1776274154 42
1776274159 42
1776274164 42
1776274169 42
1776274174 42
1776274179 42
1776274184 42
```
</details>

---

