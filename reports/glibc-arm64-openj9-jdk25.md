---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 10:00:53 EDT

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
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 165 |
| Sample Rate | 2.75/sec |
| Health Score | 172% |
| Threads | 11 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 13 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (2 unique values: 39-48 cores)</summary>

```
1790258118 48
1790258123 48
1790258128 48
1790258133 48
1790258138 48
1790258143 48
1790258148 48
1790258153 48
1790258158 39
1790258163 39
1790258168 39
1790258173 39
1790258178 39
1790258183 39
1790258188 39
1790258193 39
1790258198 39
1790258203 39
1790258208 39
1790258213 39
```
</details>

---

