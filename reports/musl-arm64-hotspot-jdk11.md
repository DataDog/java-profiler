---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 01:05:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 14 |
| Allocations | 185 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793077220 48
1793077225 48
1793077230 48
1793077235 48
1793077240 48
1793077245 48
1793077250 48
1793077255 48
1793077260 43
1793077265 43
1793077270 43
1793077275 43
1793077280 43
1793077285 43
1793077290 43
1793077295 43
1793077300 43
1793077305 43
1793077310 43
1793077315 43
```
</details>

---

