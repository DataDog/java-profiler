---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-16 09:30:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 38-58 cores)</summary>

```
1792157147 48
1792157152 48
1792157157 53
1792157162 53
1792157167 58
1792157172 58
1792157177 38
1792157182 38
1792157187 38
1792157192 38
1792157197 38
1792157202 38
1792157207 38
1792157213 38
1792157218 38
1792157223 38
1792157228 38
1792157233 38
1792157238 38
1792157243 38
```
</details>

---

