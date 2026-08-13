---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-13 03:49:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 7 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 910 |
| Sample Rate | 15.17/sec |
| Health Score | 948% |
| Threads | 8 |
| Allocations | 567 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1786607131 28
1786607136 28
1786607141 28
1786607146 28
1786607151 28
1786607156 28
1786607161 28
1786607166 28
1786607171 33
1786607176 33
1786607181 33
1786607186 33
1786607191 33
1786607196 33
1786607201 33
1786607206 33
1786607211 33
1786607216 33
1786607221 33
1786607226 33
```
</details>

---

