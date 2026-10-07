---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-07 10:47:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 11 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 13 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (5 unique values: 42-48 cores)</summary>

```
1791383981 48
1791383986 43
1791383991 43
1791383996 43
1791384001 42
1791384006 42
1791384011 42
1791384016 42
1791384022 42
1791384027 42
1791384032 42
1791384037 47
1791384042 47
1791384047 48
1791384052 48
1791384057 46
1791384062 46
1791384067 46
1791384072 46
1791384077 43
```
</details>

---

