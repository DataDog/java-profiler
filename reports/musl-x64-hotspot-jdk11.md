---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 11:44:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 802 |
| Sample Rate | 13.37/sec |
| Health Score | 836% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 87-94 cores)</summary>

```
1794587953 87
1794587958 87
1794587963 87
1794587968 87
1794587973 87
1794587978 87
1794587983 94
1794587988 94
1794587993 94
1794587998 94
1794588003 94
1794588008 94
1794588013 94
1794588018 94
1794588023 94
1794588028 94
1794588033 94
1794588038 94
1794588043 94
1794588048 94
```
</details>

---

