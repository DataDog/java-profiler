---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 08:09:20 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 270 |
| Sample Rate | 4.50/sec |
| Health Score | 281% |
| Threads | 8 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 12 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 22-34 cores)</summary>

```
1795525393 34
1795525398 34
1795525403 34
1795525408 34
1795525413 34
1795525418 34
1795525424 34
1795525429 34
1795525434 34
1795525439 34
1795525444 34
1795525449 34
1795525454 22
1795525459 22
1795525464 22
1795525469 22
1795525474 22
1795525479 22
1795525484 22
1795525489 22
```
</details>

---

