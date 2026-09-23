---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:08:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 62-78 cores)</summary>

```
1790172165 62
1790172170 62
1790172175 63
1790172180 63
1790172185 63
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
1790172251 78
1790172256 78
1790172261 78
```
</details>

---

