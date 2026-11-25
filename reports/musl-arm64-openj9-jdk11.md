---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:29:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1795630946 24
1795630951 24
1795630956 24
1795630961 24
1795630966 24
1795630971 24
1795630976 24
1795630981 24
1795630986 24
1795630991 24
1795630996 24
1795631001 24
1795631006 24
1795631011 24
1795631016 24
1795631021 24
1795631026 24
1795631031 24
1795631036 24
1795631041 24
```
</details>

---

