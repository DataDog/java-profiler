---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:29:29 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 9 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (4 unique values: 24-34 cores)</summary>

```
1795630953 34
1795630958 34
1795630963 34
1795630968 32
1795630973 32
1795630978 32
1795630983 32
1795630988 32
1795630993 32
1795630998 32
1795631003 32
1795631008 32
1795631013 34
1795631018 34
1795631023 29
1795631028 29
1795631033 29
1795631038 29
1795631043 29
1795631048 29
```
</details>

---

