---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 14:36:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 43-43 cores)</summary>

```
1790706423 43
1790706428 43
1790706433 43
1790706439 43
1790706444 43
1790706449 43
1790706454 43
1790706459 43
1790706464 43
1790706469 43
1790706474 43
1790706479 43
1790706484 43
1790706489 43
1790706494 43
1790706499 43
1790706504 43
1790706509 43
1790706514 43
1790706519 43
```
</details>

---

