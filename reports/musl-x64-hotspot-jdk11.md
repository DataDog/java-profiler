---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 10:00:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 914 |
| Sample Rate | 15.23/sec |
| Health Score | 952% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (5 unique values: 53-64 cores)</summary>

```
1790258092 53
1790258097 53
1790258102 53
1790258107 62
1790258112 62
1790258117 64
1790258122 64
1790258127 64
1790258132 64
1790258137 64
1790258142 64
1790258147 64
1790258152 64
1790258157 64
1790258162 64
1790258167 64
1790258172 64
1790258177 64
1790258182 64
1790258187 56
```
</details>

---

