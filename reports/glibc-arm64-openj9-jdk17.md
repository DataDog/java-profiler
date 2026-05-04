---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-03 21:22:12 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857501 64
1777857506 64
1777857511 64
1777857516 64
1777857521 64
1777857526 64
1777857531 64
1777857536 64
1777857541 64
1777857546 64
1777857551 64
1777857556 64
1777857561 64
1777857566 64
1777857571 64
1777857576 64
1777857581 64
1777857586 64
1777857591 64
1777857596 64
```
</details>

---

