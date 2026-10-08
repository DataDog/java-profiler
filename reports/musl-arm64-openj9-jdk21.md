---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-08 05:09:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 44-47 cores)</summary>

```
1791450279 47
1791450284 47
1791450289 47
1791450294 47
1791450299 47
1791450304 47
1791450309 47
1791450314 47
1791450319 47
1791450324 47
1791450329 47
1791450334 47
1791450339 47
1791450344 47
1791450349 47
1791450354 47
1791450359 44
1791450364 44
1791450369 44
1791450374 44
```
</details>

---

