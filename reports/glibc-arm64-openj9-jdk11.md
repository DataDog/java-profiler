---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 06:16:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 10 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 41-46 cores)</summary>

```
1793355132 46
1793355137 43
1793355142 43
1793355147 43
1793355152 43
1793355157 43
1793355162 43
1793355167 43
1793355172 43
1793355177 43
1793355182 43
1793355187 43
1793355192 43
1793355197 43
1793355202 43
1793355207 43
1793355212 43
1793355217 43
1793355222 43
1793355227 43
```
</details>

---

