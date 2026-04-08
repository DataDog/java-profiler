---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-08 13:30:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 39-56 cores)</summary>

```
1775668975 56
1775668980 56
1775668985 56
1775668990 56
1775668995 56
1775669000 56
1775669005 56
1775669010 56
1775669015 56
1775669020 56
1775669025 56
1775669030 39
1775669035 39
1775669040 39
1775669045 39
1775669050 39
1775669055 48
1775669060 48
1775669065 48
1775669070 48
```
</details>

---

