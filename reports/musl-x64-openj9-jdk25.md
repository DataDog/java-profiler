---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-06 04:35:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 11 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 13 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 74-85 cores)</summary>

```
1772789352 85
1772789357 85
1772789362 85
1772789367 85
1772789372 85
1772789377 85
1772789382 85
1772789387 85
1772789392 85
1772789397 85
1772789402 85
1772789407 85
1772789412 85
1772789417 85
1772789422 85
1772789427 85
1772789432 85
1772789437 82
1772789442 82
1772789447 82
```
</details>

---

