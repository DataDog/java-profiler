---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:28:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
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
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 864 |
| Sample Rate | 14.40/sec |
| Health Score | 900% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795630998 47
1795631003 47
1795631008 47
1795631013 47
1795631018 47
1795631023 47
1795631028 47
1795631033 47
1795631038 47
1795631043 47
1795631048 47
1795631053 47
1795631058 47
1795631063 64
1795631068 64
1795631073 47
1795631078 47
1795631083 47
1795631088 47
1795631094 47
```
</details>

---

