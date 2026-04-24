---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-24 17:04:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777064273 64
1777064278 64
1777064283 64
1777064288 64
1777064293 64
1777064298 64
1777064303 64
1777064308 64
1777064313 64
1777064318 59
1777064323 59
1777064328 59
1777064333 59
1777064338 59
1777064343 59
1777064348 59
1777064353 59
1777064358 59
1777064363 59
1777064368 59
```
</details>

---

