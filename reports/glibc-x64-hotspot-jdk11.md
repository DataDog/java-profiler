---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-13 06:03:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (4 unique values: 41-47 cores)</summary>

```
1786615122 47
1786615127 45
1786615132 45
1786615137 45
1786615142 45
1786615147 45
1786615152 45
1786615157 45
1786615162 45
1786615167 45
1786615172 45
1786615177 43
1786615182 43
1786615187 43
1786615192 43
1786615197 43
1786615202 43
1786615207 43
1786615212 43
1786615217 43
```
</details>

---

