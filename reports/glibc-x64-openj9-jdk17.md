---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 17:27:06 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 24-47 cores)</summary>

```
1792704122 24
1792704127 32
1792704132 32
1792704137 32
1792704142 32
1792704147 32
1792704152 32
1792704157 32
1792704162 32
1792704167 32
1792704172 32
1792704177 32
1792704182 32
1792704187 32
1792704192 32
1792704197 32
1792704202 32
1792704207 32
1792704212 47
1792704217 47
```
</details>

---

