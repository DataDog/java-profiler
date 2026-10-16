---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-16 09:30:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 40-51 cores)</summary>

```
1792157112 51
1792157117 51
1792157122 51
1792157127 51
1792157132 51
1792157137 51
1792157142 51
1792157147 51
1792157152 51
1792157157 51
1792157162 43
1792157167 43
1792157172 40
1792157177 40
1792157182 40
1792157187 40
1792157192 40
1792157197 40
1792157202 40
1792157207 40
```
</details>

---

