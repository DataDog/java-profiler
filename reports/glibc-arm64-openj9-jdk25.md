---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 07:23:30 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (4 unique values: 39-48 cores)</summary>

```
1793359162 48
1793359167 48
1793359172 48
1793359177 48
1793359182 48
1793359187 48
1793359192 48
1793359197 48
1793359202 48
1793359208 48
1793359213 48
1793359218 48
1793359223 48
1793359228 47
1793359233 47
1793359238 47
1793359243 47
1793359248 47
1793359253 47
1793359258 41
```
</details>

---

