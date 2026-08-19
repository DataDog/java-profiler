---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-19 04:26:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 349 |
| Sample Rate | 5.82/sec |
| Health Score | 364% |
| Threads | 11 |
| Allocations | 100 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
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
1787127767 43
1787127772 43
1787127777 43
1787127782 43
1787127787 43
```
</details>

---

