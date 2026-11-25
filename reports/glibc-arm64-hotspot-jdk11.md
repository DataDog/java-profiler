---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:28:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 925 |
| Sample Rate | 15.42/sec |
| Health Score | 964% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795630970 47
1795630975 47
1795630980 47
1795630985 47
1795630990 47
1795630995 47
1795631000 47
1795631005 47
1795631010 47
1795631015 47
1795631020 47
1795631025 47
1795631030 47
1795631035 47
1795631040 47
1795631045 47
1795631050 64
1795631055 64
1795631060 47
1795631065 47
```
</details>

---

