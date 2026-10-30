---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 11:47:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 78-82 cores)</summary>

```
1793374864 80
1793374869 80
1793374874 80
1793374879 80
1793374884 80
1793374889 80
1793374894 80
1793374899 80
1793374904 78
1793374909 78
1793374914 78
1793374919 78
1793374924 78
1793374929 78
1793374934 78
1793374939 78
1793374944 78
1793374949 78
1793374954 82
1793374959 82
```
</details>

---

