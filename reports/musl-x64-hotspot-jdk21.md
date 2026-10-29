---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-29 12:44:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 948 |
| Sample Rate | 15.80/sec |
| Health Score | 988% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 86-88 cores)</summary>

```
1793291932 86
1793291937 86
1793291942 86
1793291947 86
1793291952 86
1793291957 88
1793291962 88
1793291967 88
1793291972 88
1793291977 88
1793291982 88
1793291987 88
1793291992 88
1793291997 88
1793292002 88
1793292008 87
1793292013 87
1793292018 87
1793292023 87
1793292028 87
```
</details>

---

