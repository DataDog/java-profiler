---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:46:16 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 15 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 25-30 cores)</summary>

```
1794408079 25
1794408084 25
1794408089 25
1794408094 25
1794408099 25
1794408104 25
1794408109 25
1794408114 25
1794408119 30
1794408124 30
1794408129 30
1794408134 30
1794408139 30
1794408144 30
1794408149 30
1794408154 30
1794408159 30
1794408164 30
1794408169 30
1794408174 30
```
</details>

---

