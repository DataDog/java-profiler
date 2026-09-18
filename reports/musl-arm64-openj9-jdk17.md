---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 12:42:01 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 8 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1789749431 64
1789749436 64
1789749441 64
1789749446 64
1789749451 64
1789749456 64
1789749461 64
1789749466 64
1789749471 64
1789749476 64
1789749481 64
1789749487 47
1789749492 47
1789749497 47
1789749502 47
1789749507 47
1789749512 47
1789749517 47
1789749522 47
1789749527 47
```
</details>

---

