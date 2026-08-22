---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-22 11:45:52 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787413239 66
1787413244 66
1787413249 66
1787413254 66
1787413259 66
1787413264 66
1787413269 66
1787413274 64
1787413279 64
1787413284 64
1787413289 64
1787413294 64
1787413299 64
1787413304 64
1787413309 64
1787413314 66
1787413319 66
1787413324 66
1787413329 66
1787413334 66
```
</details>

---

