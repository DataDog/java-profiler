---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 04:42:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 31-58 cores)</summary>

```
1789979932 48
1789979937 48
1789979942 48
1789979947 48
1789979952 48
1789979957 48
1789979962 48
1789979967 58
1789979972 58
1789979977 58
1789979982 58
1789979987 58
1789979992 58
1789979997 41
1789980002 41
1789980007 41
1789980012 41
1789980017 41
1789980022 41
1789980027 41
```
</details>

---

