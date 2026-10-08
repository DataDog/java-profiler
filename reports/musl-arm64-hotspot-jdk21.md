---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:10:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (4 unique values: 39-48 cores)</summary>

```
1791468235 48
1791468240 48
1791468245 48
1791468250 48
1791468255 48
1791468260 48
1791468265 48
1791468270 48
1791468275 43
1791468280 43
1791468285 40
1791468290 40
1791468295 40
1791468300 40
1791468305 40
1791468310 40
1791468315 40
1791468320 40
1791468325 40
1791468330 40
```
</details>

---

