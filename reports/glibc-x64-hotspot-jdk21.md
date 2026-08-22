---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-22 11:45:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 14-16 cores)</summary>

```
1787413239 14
1787413244 14
1787413249 14
1787413254 14
1787413259 14
1787413264 14
1787413269 14
1787413274 16
1787413279 16
1787413284 16
1787413289 16
1787413294 16
1787413299 16
1787413304 16
1787413309 16
1787413314 16
1787413319 16
1787413324 16
1787413329 16
1787413334 16
```
</details>

---

