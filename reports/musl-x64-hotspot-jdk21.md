---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 13:47:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 65-87 cores)</summary>

```
1793644973 65
1793644978 65
1793644983 85
1793644988 85
1793644993 85
1793644998 85
1793645003 85
1793645009 85
1793645014 85
1793645019 85
1793645024 85
1793645029 85
1793645034 85
1793645039 87
1793645044 87
1793645049 87
1793645054 87
1793645059 87
1793645064 87
1793645069 87
```
</details>

---

