---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-06 04:46:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 10 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1772790196 28
1772790201 28
1772790206 28
1772790211 28
1772790216 28
1772790221 28
1772790226 28
1772790231 28
1772790236 28
1772790241 28
1772790246 32
1772790251 32
1772790256 32
1772790261 32
1772790266 32
1772790271 32
1772790276 32
1772790281 32
1772790286 32
1772790291 32
```
</details>

---

