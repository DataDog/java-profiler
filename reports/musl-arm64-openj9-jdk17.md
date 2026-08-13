---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-13 03:49:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 11 |
| Allocations | 98 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1786607116 32
1786607121 32
1786607126 32
1786607131 32
1786607136 32
1786607141 32
1786607146 32
1786607151 32
1786607156 32
1786607161 32
1786607166 32
1786607171 32
1786607176 32
1786607181 30
1786607186 30
1786607191 30
1786607196 30
1786607201 30
1786607206 30
1786607211 30
```
</details>

---

