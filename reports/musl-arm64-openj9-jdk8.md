---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-05 05:52:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1791193633 48
1791193638 48
1791193643 48
1791193648 36
1791193653 36
1791193658 36
1791193663 36
1791193668 36
1791193673 36
1791193678 36
1791193683 36
1791193688 36
1791193693 36
1791193698 36
1791193703 36
1791193708 36
1791193713 36
1791193718 36
1791193723 36
1791193728 36
```
</details>

---

