---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 11:16:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 62-66 cores)</summary>

```
1793894992 65
1793894997 65
1793895002 65
1793895007 65
1793895012 65
1793895017 65
1793895022 65
1793895027 65
1793895032 65
1793895037 65
1793895042 65
1793895047 65
1793895052 65
1793895057 66
1793895062 66
1793895067 66
1793895072 66
1793895077 66
1793895082 66
1793895087 66
```
</details>

---

