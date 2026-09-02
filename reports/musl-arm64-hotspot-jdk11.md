---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-02 05:49:13 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 14 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1788342319 46
1788342324 46
1788342329 46
1788342334 46
1788342340 46
1788342345 46
1788342350 46
1788342355 46
1788342360 46
1788342365 46
1788342370 48
1788342375 48
1788342380 48
1788342385 48
1788342390 48
1788342395 48
1788342400 48
1788342405 47
1788342410 47
1788342415 47
```
</details>

---

