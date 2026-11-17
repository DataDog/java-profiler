---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 05:58:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 13 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (4 unique values: 33-59 cores)</summary>

```
1794912867 33
1794912872 33
1794912877 33
1794912882 33
1794912887 33
1794912892 33
1794912897 33
1794912902 46
1794912907 46
1794912912 46
1794912917 46
1794912922 54
1794912927 54
1794912933 54
1794912938 54
1794912943 54
1794912948 54
1794912953 54
1794912958 54
1794912963 54
```
</details>

---

