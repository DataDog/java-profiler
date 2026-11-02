---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 13:47:26 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 70-74 cores)</summary>

```
1793644943 70
1793644948 70
1793644953 72
1793644958 72
1793644963 72
1793644968 72
1793644973 72
1793644978 72
1793644983 72
1793644988 72
1793644993 72
1793644998 72
1793645003 72
1793645008 72
1793645013 72
1793645018 72
1793645023 72
1793645028 72
1793645033 72
1793645038 72
```
</details>

---

