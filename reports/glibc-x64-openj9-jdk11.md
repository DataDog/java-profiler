---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-15 10:59:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 56-71 cores)</summary>

```
1792076017 56
1792076022 56
1792076027 56
1792076032 59
1792076037 59
1792076042 59
1792076047 59
1792076052 59
1792076057 71
1792076062 71
1792076067 71
1792076072 71
1792076077 71
1792076082 71
1792076087 71
1792076092 71
1792076097 71
1792076103 71
1792076108 71
1792076113 71
```
</details>

---

