---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 07:50:23 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 336 |
| Sample Rate | 5.60/sec |
| Health Score | 350% |
| Threads | 11 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 38-44 cores)</summary>

```
1793187782 38
1793187787 38
1793187792 38
1793187797 38
1793187802 38
1793187807 38
1793187812 38
1793187817 38
1793187822 38
1793187827 44
1793187832 44
1793187837 44
1793187842 44
1793187847 44
1793187852 44
1793187857 44
1793187862 44
1793187867 44
1793187872 44
1793187877 44
```
</details>

---

