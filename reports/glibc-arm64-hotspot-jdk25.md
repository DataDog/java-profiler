---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 05:57:59 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 13 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (4 unique values: 34-45 cores)</summary>

```
1795431283 34
1795431288 34
1795431293 34
1795431298 34
1795431303 34
1795431308 39
1795431313 39
1795431318 39
1795431323 39
1795431328 39
1795431333 39
1795431338 45
1795431343 45
1795431349 43
1795431354 43
1795431359 43
1795431364 43
1795431369 43
1795431374 43
1795431379 43
```
</details>

---

