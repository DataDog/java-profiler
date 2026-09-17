---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 16:51:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 11 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789677939 46
1789677944 46
1789677949 46
1789677954 46
1789677959 46
1789677964 46
1789677969 46
1789677974 46
1789677979 46
1789677984 48
1789677989 48
1789677994 48
1789677999 48
1789678004 48
1789678009 48
1789678014 48
1789678019 48
1789678024 48
1789678029 48
1789678034 48
```
</details>

---

