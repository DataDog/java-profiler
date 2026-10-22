---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 17:27:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 336 |
| Sample Rate | 5.60/sec |
| Health Score | 350% |
| Threads | 9 |
| Allocations | 207 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 14 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 37-47 cores)</summary>

```
1792704122 42
1792704127 42
1792704132 42
1792704137 42
1792704142 42
1792704147 42
1792704152 42
1792704157 42
1792704162 42
1792704167 42
1792704172 42
1792704177 42
1792704182 37
1792704187 37
1792704192 37
1792704197 37
1792704202 37
1792704207 37
1792704212 37
1792704217 37
```
</details>

---

