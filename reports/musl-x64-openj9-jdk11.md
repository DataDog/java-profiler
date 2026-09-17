---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 16:50:39 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 28-64 cores)</summary>

```
1789677924 64
1789677929 64
1789677934 28
1789677939 28
1789677944 28
1789677949 28
1789677954 28
1789677959 28
1789677964 28
1789677969 28
1789677974 28
1789677979 28
1789677984 28
1789677989 28
1789677994 28
1789677999 28
1789678004 28
1789678009 28
1789678014 28
1789678019 28
```
</details>

---

