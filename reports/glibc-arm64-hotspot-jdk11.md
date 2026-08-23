---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-22 20:12:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
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
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1787443534 32
1787443539 32
1787443544 32
1787443549 32
1787443554 32
1787443559 32
1787443564 32
1787443569 32
1787443574 32
1787443579 32
1787443584 32
1787443589 32
1787443594 32
1787443599 32
1787443604 32
1787443609 32
1787443614 32
1787443619 32
1787443624 32
1787443629 32
```
</details>

---

