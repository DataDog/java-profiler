---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-25 07:37:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 45 |
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
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 22-45 cores)</summary>

```
1790335970 22
1790335975 22
1790335980 22
1790335985 22
1790335990 22
1790335995 43
1790336000 43
1790336005 43
1790336010 43
1790336015 43
1790336020 43
1790336025 43
1790336030 45
1790336035 45
1790336040 45
1790336045 45
1790336050 45
1790336055 45
1790336060 45
1790336065 45
```
</details>

---

