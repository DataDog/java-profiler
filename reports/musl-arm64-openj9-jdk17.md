---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 13:29:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 277 |
| Sample Rate | 4.62/sec |
| Health Score | 289% |
| Threads | 10 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795630960 47
1795630965 47
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
1795631050 47
1795631055 64
```
</details>

---

