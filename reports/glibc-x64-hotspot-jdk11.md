---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-24 00:57:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 937 |
| Sample Rate | 15.62/sec |
| Health Score | 976% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1787547217 49
1787547222 49
1787547227 49
1787547232 51
1787547237 51
1787547242 51
1787547247 51
1787547252 51
1787547257 51
1787547262 51
1787547267 51
1787547272 51
1787547277 51
1787547282 51
1787547287 51
1787547292 51
1787547297 51
1787547303 51
1787547308 51
1787547313 51
```
</details>

---

