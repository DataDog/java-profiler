---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 09:32:46 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 11 |
| Allocations | 129 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1793194057 41
1793194062 43
1793194067 43
1793194072 43
1793194077 43
1793194082 43
1793194087 43
1793194092 48
1793194097 48
1793194102 48
1793194107 48
1793194112 48
1793194117 48
1793194122 48
1793194127 48
1793194132 48
1793194137 48
1793194142 48
1793194147 48
1793194152 48
```
</details>

---

