---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-29 12:19:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 20.60/sec |
| Health Score | 1288% |
| Threads | 11 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 890 |
| Sample Rate | 29.67/sec |
| Health Score | 1854% |
| Threads | 12 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 86-91 cores)</summary>

```
1769706843 87
1769706848 91
1769706853 91
1769706858 86
1769706863 86
1769706868 86
1769706873 86
1769706878 86
1769706883 86
1769706888 86
1769706893 86
1769706898 86
1769706903 91
1769706908 91
1769706913 91
1769706918 91
1769706923 91
1769706928 91
1769706933 91
1769706938 91
```
</details>

---

