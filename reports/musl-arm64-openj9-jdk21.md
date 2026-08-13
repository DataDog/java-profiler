---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-13 03:49:56 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1786607115 32
1786607120 32
1786607125 32
1786607130 32
1786607135 32
1786607140 32
1786607145 32
1786607150 32
1786607155 32
1786607160 32
1786607165 32
1786607170 32
1786607175 32
1786607180 30
1786607185 30
1786607190 30
1786607195 30
1786607200 30
1786607205 30
1786607210 30
```
</details>

---

