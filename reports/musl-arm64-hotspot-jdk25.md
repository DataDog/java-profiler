---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-04 05:47:27 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791107011 43
1791107016 43
1791107021 43
1791107026 43
1791107031 43
1791107036 43
1791107041 43
1791107046 43
1791107051 48
1791107056 48
1791107061 48
1791107066 48
1791107071 48
1791107076 48
1791107081 48
1791107086 48
1791107091 48
1791107096 48
1791107102 48
1791107107 48
```
</details>

---

