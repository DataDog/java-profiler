---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 11:32:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 11 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1795192090 72
1795192095 72
1795192100 72
1795192105 70
1795192110 70
1795192115 70
1795192120 70
1795192125 70
1795192130 70
1795192135 70
1795192140 70
1795192145 70
1795192150 70
1795192155 70
1795192160 70
1795192165 70
1795192170 70
1795192175 70
1795192180 70
1795192185 70
```
</details>

---

