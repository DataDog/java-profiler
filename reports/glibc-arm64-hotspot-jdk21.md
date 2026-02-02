---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-02-02 15:17:35 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 7 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1770063248 24
1770063253 24
1770063258 24
1770063263 24
1770063268 24
1770063273 24
1770063278 24
1770063283 24
1770063288 24
1770063293 24
1770063298 24
1770063303 24
1770063308 24
1770063313 24
1770063318 24
1770063323 24
1770063328 24
1770063333 24
1770063338 24
1770063343 24
```
</details>

---

