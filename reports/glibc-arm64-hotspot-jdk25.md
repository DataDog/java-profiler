---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 09:57:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 10 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795186363 50
1795186368 50
1795186373 50
1795186378 50
1795186383 50
1795186388 50
1795186394 50
1795186399 50
1795186404 50
1795186409 50
1795186414 50
1795186419 50
1795186424 50
1795186429 50
1795186434 50
1795186439 50
1795186444 50
1795186449 50
1795186454 50
1795186459 50
```
</details>

---

