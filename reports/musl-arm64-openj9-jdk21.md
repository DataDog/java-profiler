---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 06:19:12 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 7 |
| Allocations | 91 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 12 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (4 unique values: 41-45 cores)</summary>

```
1790763096 41
1790763101 41
1790763106 41
1790763111 41
1790763116 41
1790763121 41
1790763126 41
1790763131 41
1790763136 41
1790763141 41
1790763146 41
1790763151 41
1790763156 41
1790763161 41
1790763166 41
1790763171 43
1790763176 43
1790763181 43
1790763186 43
1790763191 43
```
</details>

---

