---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-11-23 11:59:24 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 830 |
| Sample Rate | 13.83/sec |
| Health Score | 864% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1795452897 83
1795452902 83
1795452907 83
1795452912 83
1795452917 85
1795452922 85
1795452927 85
1795452932 85
1795452937 85
1795452942 85
1795452947 85
1795452952 85
1795452957 85
1795452962 85
1795452967 85
1795452972 85
1795452977 85
1795452982 85
1795452987 85
1795452992 85
```
</details>

---

