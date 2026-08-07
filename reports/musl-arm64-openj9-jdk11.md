---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 13:06:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 8 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (5 unique values: 36-53 cores)</summary>

```
1786122131 53
1786122136 53
1786122141 53
1786122146 53
1786122151 41
1786122156 41
1786122161 36
1786122166 36
1786122171 36
1786122176 36
1786122181 36
1786122186 36
1786122191 47
1786122196 47
1786122201 47
1786122206 47
1786122211 47
1786122216 47
1786122221 47
1786122226 52
```
</details>

---

