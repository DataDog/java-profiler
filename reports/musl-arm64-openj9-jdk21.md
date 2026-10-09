---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-09 07:07:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791543723 43
1791543728 43
1791543733 48
1791543738 48
1791543743 48
1791543748 48
1791543753 48
1791543758 48
1791543763 48
1791543768 48
1791543773 48
1791543778 48
1791543783 48
1791543788 48
1791543793 48
1791543798 48
1791543803 48
1791543808 48
1791543813 48
1791543818 48
```
</details>

---

