---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 07:23:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793359173 48
1793359178 48
1793359183 48
1793359188 48
1793359193 48
1793359198 48
1793359203 48
1793359208 48
1793359213 48
1793359218 48
1793359223 48
1793359228 48
1793359233 48
1793359238 48
1793359243 48
1793359248 36
1793359253 36
1793359258 36
1793359263 36
1793359268 36
```
</details>

---

