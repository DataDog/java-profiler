---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-03 09:41:20 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 9 |
| Allocations | 200 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1788442526 32
1788442531 32
1788442536 32
1788442541 32
1788442546 32
1788442551 32
1788442556 32
1788442561 32
1788442566 32
1788442571 32
1788442576 32
1788442581 32
1788442586 32
1788442591 32
1788442596 32
1788442601 32
1788442606 32
1788442611 32
1788442616 32
1788442621 32
```
</details>

---

