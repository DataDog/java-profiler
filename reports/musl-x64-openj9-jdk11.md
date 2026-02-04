---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-04 13:27:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 8 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1770229126 32
1770229131 32
1770229136 32
1770229141 32
1770229146 32
1770229151 32
1770229156 32
1770229161 32
1770229166 32
1770229171 32
1770229176 32
1770229181 32
1770229186 32
1770229191 32
1770229196 32
1770229201 32
1770229206 32
1770229211 32
1770229216 32
1770229221 32
```
</details>

---

