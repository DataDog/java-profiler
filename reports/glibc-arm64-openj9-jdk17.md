---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-31 06:41:07 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 18-20 cores)</summary>

```
1788172552 20
1788172557 20
1788172562 18
1788172567 18
1788172572 18
1788172577 18
1788172582 18
1788172587 18
1788172592 18
1788172597 18
1788172602 18
1788172607 18
1788172612 18
1788172617 18
1788172622 18
1788172627 18
1788172632 18
1788172637 18
1788172642 18
1788172647 18
```
</details>

---

