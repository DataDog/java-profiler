---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 06:45:24 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 11 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 7 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 54-56 cores)</summary>

```
1786358491 54
1786358496 54
1786358501 54
1786358506 54
1786358511 54
1786358516 54
1786358521 54
1786358526 54
1786358531 56
1786358536 56
1786358541 56
1786358546 56
1786358551 56
1786358556 56
1786358561 56
1786358566 56
1786358571 56
1786358576 56
1786358581 56
1786358586 56
```
</details>

---

