---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 08:00:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 51-53 cores)</summary>

```
1792670187 53
1792670192 53
1792670197 53
1792670202 53
1792670207 53
1792670212 53
1792670217 53
1792670222 53
1792670227 53
1792670232 53
1792670237 53
1792670242 53
1792670247 53
1792670252 53
1792670257 53
1792670262 51
1792670267 51
1792670272 51
1792670277 51
1792670282 51
```
</details>

---

