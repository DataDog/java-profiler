---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 05:34:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1790242183 40
1790242188 40
1790242193 40
1790242198 40
1790242203 40
1790242208 40
1790242213 40
1790242218 40
1790242223 40
1790242228 40
1790242233 40
1790242238 40
1790242243 40
1790242248 40
1790242253 40
1790242258 40
1790242263 40
1790242268 40
1790242273 40
1790242278 40
```
</details>

---

