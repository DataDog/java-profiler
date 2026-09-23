---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 10:08:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 857 |
| Sample Rate | 14.28/sec |
| Health Score | 892% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 78-86 cores)</summary>

```
1790172151 86
1790172156 86
1790172161 78
1790172166 78
1790172171 78
1790172176 78
1790172181 78
1790172186 78
1790172191 78
1790172196 78
1790172201 78
1790172206 78
1790172211 78
1790172216 78
1790172221 78
1790172226 78
1790172231 78
1790172236 78
1790172241 78
1790172246 78
```
</details>

---

