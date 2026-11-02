---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 05:13:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 89 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 10 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793614068 30
1793614073 30
1793614078 30
1793614083 30
1793614088 30
1793614093 30
1793614098 30
1793614103 30
1793614108 30
1793614113 30
1793614118 30
1793614123 30
1793614128 30
1793614133 30
1793614138 30
1793614143 30
1793614148 30
1793614153 30
1793614158 30
1793614163 30
```
</details>

---

