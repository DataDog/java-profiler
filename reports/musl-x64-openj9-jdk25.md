---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 15:13:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 65-91 cores)</summary>

```
1793995712 65
1793995717 70
1793995722 70
1793995727 70
1793995732 70
1793995737 70
1793995742 70
1793995747 70
1793995752 70
1793995757 70
1793995762 70
1793995767 70
1793995772 70
1793995777 70
1793995782 70
1793995787 70
1793995792 91
1793995797 91
1793995802 91
1793995807 91
```
</details>

---

