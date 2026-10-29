---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-29 08:52:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 12 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793278088 48
1793278093 48
1793278098 48
1793278103 48
1793278108 48
1793278113 48
1793278118 48
1793278123 48
1793278128 48
1793278133 43
1793278138 43
1793278143 43
1793278148 43
1793278153 43
1793278158 43
1793278163 43
1793278168 43
1793278173 43
1793278178 43
1793278183 48
```
</details>

---

