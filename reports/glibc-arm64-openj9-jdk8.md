---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 13:28:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
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
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 16-28 cores)</summary>

```
1795630998 28
1795631003 28
1795631008 28
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
1795631068 16
1795631073 16
1795631078 16
1795631083 16
1795631088 16
1795631093 16
```
</details>

---

