---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-22 11:45:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 58-66 cores)</summary>

```
1787413254 66
1787413259 66
1787413264 58
1787413269 58
1787413274 58
1787413279 58
1787413284 58
1787413289 58
1787413294 58
1787413299 58
1787413304 58
1787413309 58
1787413314 58
1787413319 58
1787413324 58
1787413329 58
1787413334 58
1787413339 58
1787413344 58
1787413349 58
```
</details>

---

