---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-09 00:56:56 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 7 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 11 |
| Allocations | 103 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1786251179 30
1786251184 30
1786251189 32
1786251194 32
1786251199 32
1786251204 32
1786251209 32
1786251214 32
1786251219 32
1786251224 32
1786251229 32
1786251234 32
1786251239 32
1786251244 32
1786251249 32
1786251254 32
1786251259 32
1786251264 32
1786251269 32
1786251274 32
```
</details>

---

