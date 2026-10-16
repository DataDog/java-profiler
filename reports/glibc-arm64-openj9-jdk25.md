---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 09:30:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (6 unique values: 25-36 cores)</summary>

```
1792157162 36
1792157167 35
1792157172 35
1792157177 35
1792157182 35
1792157187 30
1792157192 30
1792157197 25
1792157202 25
1792157207 25
1792157212 25
1792157217 26
1792157222 26
1792157227 26
1792157232 26
1792157237 26
1792157242 26
1792157247 31
1792157252 31
1792157257 31
```
</details>

---

