---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:28:32 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1795630987 91
1795630992 91
1795630997 91
1795631002 91
1795631007 91
1795631012 91
1795631017 91
1795631022 91
1795631027 91
1795631032 91
1795631037 91
1795631042 89
1795631047 89
1795631052 89
1795631057 89
1795631062 89
1795631067 89
1795631072 89
1795631077 89
1795631082 89
```
</details>

---

