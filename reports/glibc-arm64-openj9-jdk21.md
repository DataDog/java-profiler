---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:36:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 28-38 cores)</summary>

```
1795113150 28
1795113155 28
1795113160 28
1795113165 28
1795113170 28
1795113175 28
1795113180 33
1795113185 33
1795113190 38
1795113195 38
1795113200 38
1795113205 38
1795113210 38
1795113215 38
1795113220 38
1795113225 38
1795113230 38
1795113235 38
1795113240 38
1795113245 38
```
</details>

---

