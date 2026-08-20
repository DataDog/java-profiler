---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-20 09:41:44 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1787233002 47
1787233007 47
1787233012 47
1787233017 47
1787233022 43
1787233027 43
1787233032 38
1787233037 38
1787233042 38
1787233047 43
1787233052 43
1787233057 43
1787233062 43
1787233067 43
1787233072 43
1787233077 43
1787233082 43
1787233087 48
1787233092 48
1787233097 48
```
</details>

---

