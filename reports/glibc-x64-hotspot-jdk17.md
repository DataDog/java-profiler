---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-13 06:03:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1786615137 27
1786615142 27
1786615147 32
1786615152 32
1786615157 32
1786615162 32
1786615167 32
1786615172 32
1786615177 32
1786615182 32
1786615187 32
1786615192 32
1786615197 32
1786615202 32
1786615207 32
1786615212 32
1786615217 32
1786615222 32
1786615227 32
1786615232 32
```
</details>

---

