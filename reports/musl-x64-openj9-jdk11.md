---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 09:57:30 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 88-92 cores)</summary>

```
1795186248 90
1795186253 90
1795186258 90
1795186263 90
1795186268 90
1795186273 90
1795186278 90
1795186284 90
1795186289 90
1795186294 90
1795186299 90
1795186304 90
1795186309 88
1795186314 88
1795186319 88
1795186324 88
1795186329 88
1795186334 90
1795186339 90
1795186344 90
```
</details>

---

