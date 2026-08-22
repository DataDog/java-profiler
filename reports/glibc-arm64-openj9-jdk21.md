---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-22 15:27:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787426616 64
1787426621 64
1787426626 64
1787426631 64
1787426636 64
1787426641 64
1787426646 64
1787426651 64
1787426656 64
1787426662 64
1787426667 64
1787426672 64
1787426677 64
1787426682 64
1787426687 64
1787426692 64
1787426697 64
1787426702 64
1787426707 64
1787426712 64
```
</details>

---

