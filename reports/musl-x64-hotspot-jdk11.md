---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-22 14:08:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 26-32 cores)</summary>

```
1776881006 32
1776881011 32
1776881016 32
1776881021 32
1776881026 32
1776881031 32
1776881036 32
1776881041 32
1776881046 32
1776881051 32
1776881056 32
1776881061 32
1776881066 32
1776881071 32
1776881076 28
1776881081 28
1776881086 28
1776881091 28
1776881096 28
1776881101 28
```
</details>

---

