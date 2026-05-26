---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-26 09:56:36 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 984 |
| Sample Rate | 16.40/sec |
| Health Score | 1025% |
| Threads | 9 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (2 unique values: 42-57 cores)</summary>

```
1779803446 57
1779803451 57
1779803456 57
1779803461 57
1779803466 57
1779803471 57
1779803476 57
1779803481 57
1779803486 57
1779803491 57
1779803496 57
1779803501 42
1779803506 42
1779803511 42
1779803516 42
1779803521 42
1779803526 42
1779803531 42
1779803536 42
1779803541 42
```
</details>

---

