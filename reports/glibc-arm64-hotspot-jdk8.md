---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-25 13:28:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1795630968 16
1795630973 16
1795630978 16
1795630983 16
1795630988 16
1795630993 16
1795630998 16
1795631003 16
1795631008 16
1795631013 16
1795631018 16
1795631023 16
1795631028 16
1795631033 16
1795631038 16
1795631043 16
1795631048 16
1795631053 16
1795631058 16
1795631063 16
```
</details>

---

