---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 09:46:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 932 |
| Sample Rate | 15.53/sec |
| Health Score | 971% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794580887 36
1794580892 36
1794580897 36
1794580902 36
1794580907 36
1794580912 36
1794580917 36
1794580922 36
1794580927 36
1794580932 36
1794580937 36
1794580942 36
1794580947 36
1794580952 48
1794580957 48
1794580962 48
1794580967 48
1794580972 48
1794580977 48
1794580982 48
```
</details>

---

