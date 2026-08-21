---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-21 09:26:24 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 10 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1787318517 48
1787318522 48
1787318527 48
1787318532 48
1787318537 48
1787318542 48
1787318547 48
1787318552 48
1787318557 48
1787318562 48
1787318567 48
1787318572 48
1787318577 47
1787318582 47
1787318587 47
1787318592 47
1787318597 48
1787318602 48
1787318607 47
1787318612 47
```
</details>

---

