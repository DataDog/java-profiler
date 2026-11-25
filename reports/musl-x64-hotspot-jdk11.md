---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:28:32 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 63-72 cores)</summary>

```
1795630950 63
1795630955 63
1795630960 63
1795630965 63
1795630970 63
1795630975 63
1795630980 63
1795630985 63
1795630990 63
1795630995 63
1795631000 63
1795631005 63
1795631010 63
1795631015 72
1795631020 72
1795631025 72
1795631030 72
1795631035 72
1795631040 72
1795631045 72
```
</details>

---

