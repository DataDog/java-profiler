---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 13:14:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (3 unique values: 22-46 cores)</summary>

```
1790096995 22
1790097000 22
1790097005 22
1790097010 22
1790097015 22
1790097020 22
1790097025 22
1790097030 22
1790097035 22
1790097040 22
1790097045 46
1790097050 46
1790097055 46
1790097060 46
1790097065 46
1790097070 46
1790097075 46
1790097080 46
1790097085 36
1790097090 36
```
</details>

---

