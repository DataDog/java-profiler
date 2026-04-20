---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 04:41:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (5 unique values: 79-96 cores)</summary>

```
1776674128 86
1776674133 86
1776674138 86
1776674143 86
1776674148 86
1776674153 96
1776674158 96
1776674163 96
1776674168 96
1776674173 86
1776674178 86
1776674183 84
1776674188 84
1776674193 84
1776674198 84
1776674203 84
1776674208 84
1776674213 84
1776674218 82
1776674223 82
```
</details>

---

