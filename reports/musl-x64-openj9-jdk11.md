---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 17:02:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 955 |
| Sample Rate | 15.92/sec |
| Health Score | 995% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (4 unique values: 72-94 cores)</summary>

```
1794434254 92
1794434259 94
1794434264 94
1794434269 94
1794434274 94
1794434279 94
1794434284 94
1794434289 72
1794434294 72
1794434299 72
1794434304 72
1794434309 72
1794434314 72
1794434319 72
1794434324 72
1794434329 72
1794434334 74
1794434339 74
1794434344 74
1794434349 74
```
</details>

---

