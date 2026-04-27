---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-26 21:26:01 EDT

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
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 13 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1777252611 32
1777252616 32
1777252621 32
1777252626 32
1777252631 32
1777252636 32
1777252641 32
1777252646 32
1777252651 32
1777252656 32
1777252661 32
1777252666 32
1777252671 32
1777252676 32
1777252681 32
1777252686 32
1777252692 32
1777252697 32
1777252702 32
1777252707 32
```
</details>

---

