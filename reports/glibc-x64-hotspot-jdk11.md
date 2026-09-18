---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 05:26:35 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 48-56 cores)</summary>

```
1789723352 50
1789723358 50
1789723363 50
1789723368 50
1789723373 50
1789723378 50
1789723383 48
1789723388 48
1789723393 48
1789723398 48
1789723403 48
1789723408 48
1789723413 48
1789723418 48
1789723423 48
1789723428 48
1789723433 48
1789723438 56
1789723443 56
1789723448 56
```
</details>

---

