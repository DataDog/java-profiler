---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-08 13:30:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (5 unique values: 51-62 cores)</summary>

```
1775668975 60
1775668980 60
1775668985 60
1775668990 62
1775668995 62
1775669000 55
1775669005 55
1775669010 55
1775669015 53
1775669020 53
1775669025 53
1775669030 53
1775669035 53
1775669040 53
1775669045 51
1775669050 51
1775669055 51
1775669060 51
1775669065 51
1775669070 51
```
</details>

---

