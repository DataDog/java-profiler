---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 12:36:28 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (3 unique values: 48-64 cores)</summary>

```
1795455163 49
1795455168 49
1795455173 49
1795455178 49
1795455183 64
1795455188 64
1795455193 64
1795455198 48
1795455203 48
1795455208 48
1795455213 48
1795455218 48
1795455223 48
1795455228 48
1795455233 48
1795455238 48
1795455243 48
1795455248 48
1795455254 48
1795455259 48
```
</details>

---

