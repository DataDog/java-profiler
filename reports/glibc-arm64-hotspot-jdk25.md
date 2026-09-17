---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 18:02:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 2.65/sec |
| Health Score | 166% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 11 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1789682213 28
1789682218 28
1789682223 28
1789682228 28
1789682233 28
1789682238 33
1789682243 33
1789682248 33
1789682253 33
1789682258 33
1789682263 33
1789682268 33
1789682273 33
1789682278 33
1789682283 33
1789682288 33
1789682293 33
1789682298 33
1789682303 33
1789682308 33
```
</details>

---

