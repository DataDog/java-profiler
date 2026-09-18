---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:08:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 13 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1789743354 42
1789743359 42
1789743364 42
1789743369 42
1789743374 42
1789743379 47
1789743384 47
1789743389 47
1789743394 47
1789743399 47
1789743404 47
1789743409 47
1789743414 47
1789743419 47
1789743424 47
1789743429 47
1789743434 47
1789743439 47
1789743444 47
1789743449 47
```
</details>

---

