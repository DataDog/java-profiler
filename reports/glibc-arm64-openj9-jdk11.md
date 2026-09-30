---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 06:49:41 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 8 |
| Allocations | 33 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1790765062 40
1790765067 40
1790765072 40
1790765077 40
1790765082 40
1790765087 40
1790765092 40
1790765097 40
1790765102 40
1790765107 40
1790765112 40
1790765117 40
1790765122 40
1790765127 40
1790765132 40
1790765137 45
1790765142 45
1790765147 45
1790765152 45
1790765157 45
```
</details>

---

