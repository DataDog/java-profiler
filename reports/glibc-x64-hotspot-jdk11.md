---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-11 14:07:37 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 58-60 cores)</summary>

```
1773252198 60
1773252203 60
1773252208 60
1773252213 60
1773252218 60
1773252223 60
1773252228 60
1773252233 60
1773252238 60
1773252243 60
1773252248 60
1773252253 60
1773252258 60
1773252263 60
1773252268 60
1773252273 60
1773252278 60
1773252283 58
1773252288 58
1773252293 58
```
</details>

---

