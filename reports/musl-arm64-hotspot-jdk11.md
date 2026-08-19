---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-19 06:13:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 14 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1787134050 47
1787134055 47
1787134060 47
1787134065 47
1787134070 47
1787134075 47
1787134080 47
1787134085 47
1787134090 47
1787134095 47
1787134100 47
1787134105 47
1787134110 47
1787134115 47
1787134120 47
1787134125 47
1787134130 52
1787134135 52
1787134140 52
1787134145 52
```
</details>

---

