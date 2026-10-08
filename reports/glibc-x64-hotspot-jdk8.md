---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-08 10:10:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1791468215 27
1791468220 27
1791468225 27
1791468230 27
1791468235 29
1791468240 29
1791468245 29
1791468250 29
1791468255 29
1791468260 29
1791468265 29
1791468270 29
1791468275 27
1791468280 27
1791468285 27
1791468290 27
1791468295 27
1791468300 27
1791468305 27
1791468310 27
```
</details>

---

