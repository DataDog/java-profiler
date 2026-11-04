---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-04 08:54:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 78-94 cores)</summary>

```
1793800137 94
1793800142 78
1793800147 78
1793800152 78
1793800157 78
1793800162 78
1793800167 78
1793800172 78
1793800177 78
1793800182 78
1793800187 78
1793800192 78
1793800197 78
1793800202 78
1793800207 78
1793800212 78
1793800217 78
1793800222 78
1793800227 78
1793800232 78
```
</details>

---

