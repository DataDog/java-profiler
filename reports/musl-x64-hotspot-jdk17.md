---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-12 05:20:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (4 unique values: 16-28 cores)</summary>

```
1786526122 16
1786526127 16
1786526132 26
1786526137 26
1786526142 26
1786526147 26
1786526152 26
1786526157 26
1786526162 26
1786526167 26
1786526172 26
1786526177 24
1786526182 24
1786526187 26
1786526192 26
1786526197 26
1786526202 26
1786526207 26
1786526212 26
1786526217 26
```
</details>

---

