---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 11:10:55 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 13 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1794240189 48
1794240194 48
1794240199 48
1794240204 48
1794240209 48
1794240214 48
1794240219 48
1794240224 48
1794240229 48
1794240234 48
1794240239 48
1794240244 48
1794240249 48
1794240254 48
1794240259 48
1794240264 48
1794240269 48
1794240274 48
1794240280 48
1794240285 48
```
</details>

---

