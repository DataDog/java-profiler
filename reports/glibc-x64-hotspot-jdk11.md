---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-28 18:13:24 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 814 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1777413997 64
1777414002 64
1777414007 64
1777414012 64
1777414017 64
1777414022 64
1777414027 62
1777414032 62
1777414037 62
1777414042 62
1777414047 62
1777414052 62
1777414057 64
1777414062 64
1777414067 64
1777414072 64
1777414077 64
1777414082 64
1777414087 64
1777414092 64
```
</details>

---

