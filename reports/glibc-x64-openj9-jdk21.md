---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-16 09:30:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 21-24 cores)</summary>

```
1792157147 22
1792157152 22
1792157157 22
1792157162 22
1792157167 22
1792157172 22
1792157177 22
1792157182 22
1792157187 22
1792157192 22
1792157197 22
1792157202 22
1792157207 22
1792157212 22
1792157217 22
1792157222 24
1792157227 24
1792157232 24
1792157237 24
1792157242 21
```
</details>

---

