---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 10:05:23 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 12 |
| Allocations | 186 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1792591234 48
1792591239 48
1792591244 48
1792591249 48
1792591254 48
1792591259 48
1792591264 48
1792591269 48
1792591274 48
1792591279 48
1792591284 48
1792591289 48
1792591294 48
1792591299 48
1792591304 48
1792591309 48
1792591314 48
1792591319 48
1792591324 48
1792591329 48
```
</details>

---

