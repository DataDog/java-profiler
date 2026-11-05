---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 05:42:58 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 10 |
| Allocations | 179 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (5 unique values: 40-46 cores)</summary>

```
1793875163 45
1793875168 45
1793875173 45
1793875178 45
1793875183 45
1793875188 45
1793875193 45
1793875198 45
1793875203 45
1793875208 45
1793875213 45
1793875218 40
1793875223 40
1793875228 40
1793875233 43
1793875238 43
1793875243 43
1793875248 43
1793875253 43
1793875258 43
```
</details>

---

