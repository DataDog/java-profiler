---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-09 03:39:38 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 8 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 949 |
| Sample Rate | 15.82/sec |
| Health Score | 989% |
| Threads | 9 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1791531218 30
1791531223 32
1791531228 32
1791531233 32
1791531238 32
1791531243 30
1791531248 30
1791531253 28
1791531258 28
1791531263 28
1791531268 28
1791531273 28
1791531278 28
1791531283 28
1791531288 28
1791531293 28
1791531298 28
1791531303 28
1791531308 28
1791531313 28
```
</details>

---

