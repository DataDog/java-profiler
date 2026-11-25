---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 13:30:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 12 |
| Allocations | 86 |

<details>
<summary>CPU Timeline (3 unique values: 28-34 cores)</summary>

```
1795631115 29
1795631120 29
1795631125 34
1795631130 34
1795631135 29
1795631140 29
1795631145 29
1795631150 29
1795631155 29
1795631160 29
1795631165 29
1795631170 29
1795631175 29
1795631180 29
1795631185 29
1795631190 29
1795631195 29
1795631200 29
1795631205 34
1795631210 34
```
</details>

---

