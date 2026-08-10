---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 06:10:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 828 |
| Sample Rate | 13.80/sec |
| Health Score | 862% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 38-70 cores)</summary>

```
1786356260 64
1786356265 64
1786356270 64
1786356275 64
1786356280 64
1786356285 64
1786356290 64
1786356295 64
1786356300 64
1786356305 38
1786356310 38
1786356315 38
1786356320 38
1786356325 38
1786356330 38
1786356335 38
1786356340 38
1786356345 38
1786356350 38
1786356355 38
```
</details>

---

