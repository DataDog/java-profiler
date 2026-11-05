---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 11:16:26 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 10 |
| Allocations | 153 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1793895133 64
1793895138 64
1793895143 64
1793895148 64
1793895153 64
1793895158 64
1793895163 64
1793895168 64
1793895173 64
1793895178 64
1793895183 64
1793895188 64
1793895193 64
1793895198 64
1793895203 64
1793895208 64
1793895213 64
1793895218 64
1793895223 64
1793895228 64
```
</details>

---

