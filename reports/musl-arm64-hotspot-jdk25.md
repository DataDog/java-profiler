---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 03:05:53 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 252 |
| Sample Rate | 4.20/sec |
| Health Score | 262% |
| Threads | 9 |
| Allocations | 139 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 15 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790665320 43
1790665325 43
1790665330 43
1790665335 43
1790665340 43
1790665345 43
1790665350 43
1790665355 43
1790665360 43
1790665365 43
1790665370 43
1790665375 43
1790665380 43
1790665385 43
1790665390 43
1790665395 43
1790665400 38
1790665405 38
1790665410 38
1790665415 38
```
</details>

---

