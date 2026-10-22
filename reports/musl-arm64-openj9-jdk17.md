---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 08:00:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 51-53 cores)</summary>

```
1792670167 53
1792670172 53
1792670177 53
1792670182 53
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
1792670252 51
1792670257 51
1792670262 51
```
</details>

---

