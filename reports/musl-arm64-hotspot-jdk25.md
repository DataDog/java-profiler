---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-24 09:28:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 11 |
| Allocations | 178 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 39-48 cores)</summary>

```
1787577822 39
1787577827 39
1787577832 39
1787577837 39
1787577842 39
1787577847 39
1787577852 39
1787577857 39
1787577862 39
1787577867 39
1787577872 48
1787577877 48
1787577882 48
1787577887 48
1787577892 48
1787577897 48
1787577902 48
1787577907 48
1787577912 48
1787577917 48
```
</details>

---

