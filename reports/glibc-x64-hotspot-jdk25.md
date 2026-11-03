---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 16:51:00 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 61-77 cores)</summary>

```
1793742208 77
1793742213 77
1793742218 77
1793742223 77
1793742228 77
1793742233 77
1793742238 72
1793742243 72
1793742248 72
1793742253 72
1793742258 72
1793742263 72
1793742268 72
1793742273 72
1793742278 72
1793742283 72
1793742288 72
1793742293 72
1793742298 72
1793742303 72
```
</details>

---

