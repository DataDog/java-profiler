---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 09:45:18 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 10 |
| Allocations | 128 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 10 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793281230 51
1793281235 51
1793281240 51
1793281245 51
1793281250 51
1793281255 51
1793281260 51
1793281265 46
1793281270 46
1793281275 46
1793281280 46
1793281285 46
1793281290 46
1793281295 46
1793281300 46
1793281305 46
1793281310 46
1793281315 46
1793281320 46
1793281325 51
```
</details>

---

