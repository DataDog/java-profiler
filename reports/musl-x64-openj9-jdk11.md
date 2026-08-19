---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-19 13:04:21 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 71-88 cores)</summary>

```
1787158819 88
1787158824 88
1787158829 88
1787158834 88
1787158839 88
1787158844 88
1787158849 88
1787158854 88
1787158859 88
1787158864 88
1787158869 88
1787158874 88
1787158879 83
1787158884 83
1787158889 83
1787158894 83
1787158899 83
1787158904 83
1787158909 83
1787158914 83
```
</details>

---

