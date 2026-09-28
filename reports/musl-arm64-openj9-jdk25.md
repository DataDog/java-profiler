---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 06:45:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 41-46 cores)</summary>

```
1790592070 46
1790592075 41
1790592080 41
1790592085 43
1790592090 43
1790592096 43
1790592101 43
1790592106 43
1790592111 43
1790592116 43
1790592121 43
1790592126 43
1790592131 43
1790592136 43
1790592141 43
1790592146 43
1790592151 43
1790592156 43
1790592161 43
1790592166 43
```
</details>

---

