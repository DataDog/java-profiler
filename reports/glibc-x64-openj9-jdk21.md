---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-20 17:39:40 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 84-90 cores)</summary>

```
1792532052 84
1792532057 84
1792532062 84
1792532067 84
1792532072 84
1792532077 84
1792532082 84
1792532087 86
1792532092 86
1792532097 88
1792532102 88
1792532107 88
1792532112 88
1792532117 88
1792532122 88
1792532127 88
1792532132 88
1792532137 88
1792532142 88
1792532147 88
```
</details>

---

