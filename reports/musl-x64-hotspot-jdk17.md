---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-01 09:14:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 849 |
| Sample Rate | 14.15/sec |
| Health Score | 884% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1777640928 46
1777640933 46
1777640938 51
1777640943 51
1777640948 51
1777640953 51
1777640958 51
1777640963 51
1777640968 51
1777640973 51
1777640978 51
1777640983 51
1777640988 51
1777640993 51
1777640998 51
1777641003 51
1777641008 51
1777641013 51
1777641018 51
1777641023 51
```
</details>

---

