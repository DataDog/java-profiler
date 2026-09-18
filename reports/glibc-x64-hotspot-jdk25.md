---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 05:26:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 46-61 cores)</summary>

```
1789723368 61
1789723373 61
1789723378 61
1789723383 61
1789723388 61
1789723393 51
1789723398 51
1789723403 46
1789723408 46
1789723413 46
1789723418 46
1789723423 46
1789723428 46
1789723433 46
1789723438 46
1789723443 46
1789723448 46
1789723453 46
1789723458 46
1789723463 46
```
</details>

---

