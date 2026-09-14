---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-14 12:04:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 7 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1789401521 36
1789401526 36
1789401531 36
1789401536 36
1789401541 36
1789401546 36
1789401551 36
1789401556 36
1789401561 36
1789401566 36
1789401571 36
1789401576 36
1789401581 45
1789401586 45
1789401591 45
1789401596 45
1789401601 45
1789401606 45
1789401611 45
1789401616 45
```
</details>

---

