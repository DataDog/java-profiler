---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:28:31 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795630975 43
1795630980 43
1795630985 48
1795630990 48
1795630995 48
1795631000 48
1795631005 48
1795631010 48
1795631015 48
1795631020 48
1795631025 48
1795631030 48
1795631035 48
1795631040 48
1795631045 48
1795631050 48
1795631055 48
1795631060 48
1795631065 48
1795631070 48
```
</details>

---

