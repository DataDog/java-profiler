---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 07:05:21 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 276 |
| Sample Rate | 4.60/sec |
| Health Score | 287% |
| Threads | 10 |
| Allocations | 144 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 11 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (3 unique values: 25-30 cores)</summary>

```
1795608091 25
1795608096 25
1795608101 25
1795608106 30
1795608111 30
1795608116 30
1795608121 30
1795608126 30
1795608131 30
1795608136 30
1795608141 30
1795608146 30
1795608151 30
1795608156 29
1795608161 29
1795608166 29
1795608171 29
1795608176 29
1795608181 29
1795608186 29
```
</details>

---

