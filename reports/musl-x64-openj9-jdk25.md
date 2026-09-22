---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 13:14:52 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 66-74 cores)</summary>

```
1790096990 68
1790096995 68
1790097000 68
1790097005 68
1790097010 68
1790097015 68
1790097020 68
1790097025 68
1790097030 68
1790097035 68
1790097040 68
1790097045 68
1790097050 68
1790097055 68
1790097060 66
1790097065 66
1790097071 66
1790097076 66
1790097081 66
1790097086 66
```
</details>

---

