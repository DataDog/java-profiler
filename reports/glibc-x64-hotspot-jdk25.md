---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 08:46:38 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (4 unique values: 84-90 cores)</summary>

```
1792672935 84
1792672940 84
1792672945 84
1792672950 84
1792672955 84
1792672960 84
1792672965 84
1792672970 86
1792672975 86
1792672980 86
1792672985 86
1792672990 86
1792672995 86
1792673000 86
1792673005 86
1792673010 86
1792673015 86
1792673020 86
1792673025 86
1792673030 86
```
</details>

---

