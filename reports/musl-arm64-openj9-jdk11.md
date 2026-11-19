---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:36:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 12 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795113113 50
1795113118 50
1795113123 50
1795113128 50
1795113133 50
1795113138 64
1795113143 64
1795113148 50
1795113153 50
1795113158 50
1795113163 50
1795113168 50
1795113173 50
1795113178 50
1795113183 50
1795113188 50
1795113193 50
1795113198 50
1795113203 50
1795113208 50
```
</details>

---

