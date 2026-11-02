---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 13:47:24 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 12 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 13 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793645012 46
1793645017 48
1793645022 48
1793645027 48
1793645032 48
1793645037 48
1793645042 48
1793645048 48
1793645053 48
1793645058 48
1793645063 48
1793645068 48
1793645073 48
1793645078 48
1793645083 48
1793645088 48
1793645093 48
1793645098 43
1793645103 43
1793645108 43
```
</details>

---

