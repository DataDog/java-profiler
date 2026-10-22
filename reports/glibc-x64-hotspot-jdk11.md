---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 11:42:29 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 9 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 52-59 cores)</summary>

```
1792683227 52
1792683232 52
1792683237 52
1792683242 54
1792683247 54
1792683252 54
1792683257 54
1792683262 54
1792683267 54
1792683272 54
1792683277 54
1792683282 54
1792683287 54
1792683292 54
1792683297 54
1792683302 54
1792683307 59
1792683312 59
1792683317 59
1792683322 59
```
</details>

---

