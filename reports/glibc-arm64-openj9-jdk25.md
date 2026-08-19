---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-19 04:26:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 15 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787127667 46
1787127672 46
1787127677 46
1787127682 46
1787127687 46
1787127692 46
1787127697 46
1787127702 48
1787127707 48
1787127712 43
1787127717 43
1787127722 43
1787127727 43
1787127732 43
1787127737 43
1787127742 43
1787127747 43
1787127752 43
1787127757 43
1787127762 43
```
</details>

---

