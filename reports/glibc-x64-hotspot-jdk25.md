---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 13:28:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (4 unique values: 91-96 cores)</summary>

```
1795630996 94
1795631001 94
1795631006 94
1795631011 94
1795631016 94
1795631021 94
1795631026 94
1795631031 94
1795631036 96
1795631041 96
1795631046 96
1795631051 96
1795631056 93
1795631061 93
1795631066 93
1795631071 93
1795631076 93
1795631081 93
1795631086 93
1795631091 93
```
</details>

---

