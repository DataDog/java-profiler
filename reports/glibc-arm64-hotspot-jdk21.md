---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 13:04:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 10 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1795543248 41
1795543253 41
1795543258 41
1795543263 46
1795543268 46
1795543273 45
1795543278 45
1795543283 45
1795543288 45
1795543293 45
1795543298 45
1795543303 45
1795543308 45
1795543313 45
1795543318 45
1795543323 45
1795543328 45
1795543333 46
1795543338 46
1795543343 46
```
</details>

---

