---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 06:06:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 8 |
| Allocations | 102 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (4 unique values: 24-51 cores)</summary>

```
1795085992 39
1795085997 39
1795086002 39
1795086007 39
1795086012 39
1795086017 39
1795086022 39
1795086027 39
1795086032 39
1795086037 39
1795086042 39
1795086047 39
1795086052 39
1795086057 39
1795086062 39
1795086067 39
1795086072 39
1795086077 39
1795086082 51
1795086087 51
```
</details>

---

