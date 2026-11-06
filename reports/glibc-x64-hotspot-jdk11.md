---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 19:20:34 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (3 unique values: 32-39 cores)</summary>

```
1793924178 34
1793924183 32
1793924188 32
1793924193 32
1793924198 32
1793924203 34
1793924208 34
1793924213 34
1793924218 34
1793924223 34
1793924228 34
1793924233 34
1793924238 34
1793924243 34
1793924248 34
1793924253 34
1793924258 34
1793924263 34
1793924268 34
1793924273 34
```
</details>

---

