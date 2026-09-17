---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 06:26:37 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 7 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 12 |
| Allocations | 88 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1789640486 48
1789640491 48
1789640496 48
1789640501 48
1789640506 48
1789640511 48
1789640516 48
1789640521 48
1789640526 48
1789640531 48
1789640536 48
1789640541 48
1789640546 48
1789640551 48
1789640556 48
1789640561 48
1789640566 47
1789640571 47
1789640576 47
1789640581 47
```
</details>

---

