---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-20 09:29:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 42-46 cores)</summary>

```
1776691545 45
1776691550 45
1776691555 45
1776691560 45
1776691565 45
1776691570 42
1776691575 42
1776691580 42
1776691585 42
1776691590 42
1776691595 42
1776691600 42
1776691605 42
1776691610 42
1776691615 42
1776691620 42
1776691625 42
1776691630 42
1776691635 42
1776691640 42
```
</details>

---

