---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:14:00 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 41-48 cores)</summary>

```
1789743324 41
1789743329 41
1789743334 41
1789743339 41
1789743344 41
1789743349 41
1789743354 41
1789743359 41
1789743364 41
1789743369 41
1789743374 41
1789743379 41
1789743384 41
1789743389 41
1789743394 41
1789743399 48
1789743404 48
1789743409 48
1789743414 48
1789743419 48
```
</details>

---

