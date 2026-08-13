---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-13 06:03:06 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 9 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (5 unique values: 10-34 cores)</summary>

```
1786615138 34
1786615143 34
1786615148 34
1786615153 34
1786615158 34
1786615163 34
1786615168 34
1786615173 34
1786615178 34
1786615183 34
1786615188 34
1786615193 34
1786615198 34
1786615203 34
1786615208 34
1786615213 34
1786615218 34
1786615223 34
1786615228 34
1786615233 29
```
</details>

---

