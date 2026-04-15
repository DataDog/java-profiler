---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-15 10:34:51 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 399 |
| Sample Rate | 6.65/sec |
| Health Score | 416% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 25-30 cores)</summary>

```
1776263148 25
1776263153 25
1776263158 25
1776263163 25
1776263168 25
1776263173 28
1776263178 28
1776263183 28
1776263188 28
1776263193 28
1776263198 28
1776263203 28
1776263208 28
1776263213 28
1776263218 28
1776263223 28
1776263228 28
1776263233 28
1776263238 28
1776263243 28
```
</details>

---

