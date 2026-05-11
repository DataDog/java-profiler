---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-11 18:22:08 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1778537956 60
1778537961 60
1778537966 60
1778537971 60
1778537976 60
1778537981 60
1778537986 60
1778537991 60
1778537996 60
1778538001 60
1778538006 60
1778538011 60
1778538016 60
1778538021 60
1778538026 60
1778538031 64
1778538036 64
1778538041 64
1778538046 64
1778538051 64
```
</details>

---

