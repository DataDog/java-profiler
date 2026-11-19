---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 08:02:15 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 9 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 10 |
| Allocations | 103 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795093132 50
1795093137 50
1795093142 50
1795093147 50
1795093152 50
1795093157 50
1795093162 50
1795093167 50
1795093172 50
1795093177 50
1795093182 50
1795093187 50
1795093192 45
1795093197 45
1795093202 45
1795093207 45
1795093212 45
1795093217 45
1795093222 45
1795093227 45
```
</details>

---

