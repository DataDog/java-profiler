---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-28 09:37:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 9 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1777383252 32
1777383257 32
1777383262 32
1777383267 32
1777383272 32
1777383277 32
1777383282 32
1777383287 32
1777383292 32
1777383297 32
1777383302 32
1777383307 32
1777383312 32
1777383317 28
1777383322 28
1777383327 28
1777383332 28
1777383337 28
1777383342 28
1777383347 28
```
</details>

---

