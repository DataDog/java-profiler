---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 06:01:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 49-72 cores)</summary>

```
1794480941 49
1794480946 49
1794480951 49
1794480956 49
1794480961 49
1794480966 49
1794480971 69
1794480976 69
1794480981 69
1794480986 69
1794480991 69
1794480996 69
1794481001 71
1794481006 71
1794481011 69
1794481016 69
1794481021 69
1794481026 69
1794481032 69
1794481037 69
```
</details>

---

