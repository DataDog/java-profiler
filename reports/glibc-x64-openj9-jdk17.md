---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-27 09:00:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 20.83/sec |
| Health Score | 1302% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1769514157 64
1769514162 64
1769514167 64
1769514172 64
1769514177 64
1769514182 64
1769514187 64
1769514192 64
1769514197 64
1769514202 64
1769514207 64
1769514212 64
1769514217 64
1769514222 64
1769514227 64
1769514232 64
1769514237 64
1769514242 64
1769514247 64
1769514252 59
```
</details>

---

