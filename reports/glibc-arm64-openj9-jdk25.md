---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 16:43:55 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 244 |
| Sample Rate | 4.07/sec |
| Health Score | 254% |
| Threads | 14 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 24-36 cores)</summary>

```
1794001197 24
1794001202 24
1794001207 24
1794001212 24
1794001217 24
1794001222 24
1794001227 24
1794001232 24
1794001237 24
1794001242 24
1794001247 24
1794001252 24
1794001257 24
1794001262 24
1794001267 24
1794001272 24
1794001277 36
1794001282 36
1794001287 36
1794001292 36
```
</details>

---

