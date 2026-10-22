---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 09:57:26 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 235 |
| Sample Rate | 3.92/sec |
| Health Score | 245% |
| Threads | 14 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792677094 48
1792677099 48
1792677104 48
1792677109 48
1792677114 48
1792677119 48
1792677124 48
1792677129 48
1792677134 48
1792677139 48
1792677144 48
1792677149 48
1792677154 48
1792677159 48
1792677164 48
1792677169 48
1792677174 48
1792677179 48
1792677185 48
1792677190 48
```
</details>

---

