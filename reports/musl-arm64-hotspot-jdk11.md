---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 10:11:27 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 33 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1786457190 13
1786457195 13
1786457200 13
1786457205 13
1786457210 13
1786457215 13
1786457220 13
1786457225 13
1786457230 13
1786457235 13
1786457240 13
1786457245 13
1786457250 13
1786457255 18
1786457260 18
1786457265 18
1786457270 18
1786457275 18
1786457280 18
1786457285 18
```
</details>

---

