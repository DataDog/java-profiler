---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 09:57:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 12 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (5 unique values: 70-88 cores)</summary>

```
1795186288 72
1795186293 72
1795186298 72
1795186303 72
1795186308 72
1795186313 70
1795186318 70
1795186323 70
1795186328 70
1795186333 70
1795186338 70
1795186343 70
1795186348 81
1795186353 81
1795186358 83
1795186363 83
1795186368 83
1795186373 81
1795186378 81
1795186383 88
```
</details>

---

