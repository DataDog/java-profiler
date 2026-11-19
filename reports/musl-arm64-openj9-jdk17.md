---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 08:32:31 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 12 |
| Allocations | 171 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 15 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 18-38 cores)</summary>

```
1795094833 38
1795094838 38
1795094843 38
1795094848 38
1795094853 38
1795094858 38
1795094863 38
1795094868 38
1795094873 38
1795094878 38
1795094883 38
1795094888 38
1795094893 38
1795094898 38
1795094903 38
1795094908 18
1795094913 18
1795094918 18
1795094923 18
1795094928 18
```
</details>

---

