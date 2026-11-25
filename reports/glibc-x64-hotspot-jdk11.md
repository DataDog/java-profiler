---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:28:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 87-96 cores)</summary>

```
1795630961 87
1795630966 87
1795630971 87
1795630976 87
1795630981 87
1795630986 87
1795630991 87
1795630996 87
1795631001 87
1795631006 87
1795631011 96
1795631016 96
1795631021 96
1795631026 96
1795631031 96
1795631036 96
1795631041 96
1795631046 96
1795631051 96
1795631056 96
```
</details>

---

