---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-25 00:58:50 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (6 unique values: 38-52 cores)</summary>

```
1790312062 50
1790312067 50
1790312072 44
1790312077 44
1790312082 48
1790312087 48
1790312092 48
1790312097 50
1790312102 50
1790312107 52
1790312112 52
1790312117 52
1790312122 52
1790312127 48
1790312132 48
1790312137 48
1790312142 38
1790312147 38
1790312152 38
1790312157 38
```
</details>

---

