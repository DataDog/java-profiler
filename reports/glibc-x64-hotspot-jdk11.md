---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-26 16:19:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 889 |
| Sample Rate | 14.82/sec |
| Health Score | 926% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1787775239 86
1787775244 86
1787775249 86
1787775254 86
1787775259 86
1787775264 86
1787775269 86
1787775274 86
1787775279 86
1787775284 86
1787775289 86
1787775294 86
1787775299 86
1787775304 86
1787775309 86
1787775314 86
1787775319 86
1787775324 84
1787775329 84
1787775334 86
```
</details>

---

