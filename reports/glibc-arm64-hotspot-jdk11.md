---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 11:54:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 13 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793638099 43
1793638104 43
1793638109 43
1793638114 48
1793638119 48
1793638124 48
1793638129 48
1793638134 48
1793638139 48
1793638144 48
1793638149 48
1793638154 48
1793638159 48
1793638164 48
1793638169 48
1793638174 48
1793638179 48
1793638184 48
1793638189 48
1793638194 48
```
</details>

---

