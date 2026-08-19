---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-19 10:53:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
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
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787150864 43
1787150869 48
1787150874 48
1787150879 48
1787150884 48
1787150889 48
1787150894 48
1787150899 48
1787150904 48
1787150909 48
1787150914 48
1787150919 48
1787150924 48
1787150929 48
1787150934 48
1787150939 48
1787150944 48
1787150949 48
1787150954 48
1787150959 48
```
</details>

---

