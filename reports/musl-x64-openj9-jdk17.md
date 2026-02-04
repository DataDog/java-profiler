---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-04 10:55:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1770220096 32
1770220101 32
1770220106 32
1770220111 32
1770220116 32
1770220121 32
1770220126 32
1770220131 32
1770220136 32
1770220141 32
1770220146 32
1770220151 32
1770220156 32
1770220161 32
1770220166 32
1770220171 32
1770220176 32
1770220181 32
1770220186 32
1770220191 32
```
</details>

---

