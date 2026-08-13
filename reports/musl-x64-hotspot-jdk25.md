---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-13 06:03:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 12 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 83-86 cores)</summary>

```
1786615120 86
1786615125 86
1786615130 86
1786615135 86
1786615140 86
1786615145 86
1786615150 86
1786615155 86
1786615160 86
1786615165 86
1786615170 86
1786615175 83
1786615180 83
1786615185 83
1786615190 83
1786615195 83
1786615200 83
1786615205 83
1786615210 83
1786615215 83
```
</details>

---

