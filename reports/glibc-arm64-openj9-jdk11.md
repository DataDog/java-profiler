---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 06:19:10 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 353 |
| Sample Rate | 5.88/sec |
| Health Score | 368% |
| Threads | 11 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 28-36 cores)</summary>

```
1790763158 36
1790763163 36
1790763168 36
1790763173 36
1790763178 36
1790763183 36
1790763188 36
1790763193 36
1790763198 36
1790763203 36
1790763208 36
1790763213 36
1790763218 36
1790763223 36
1790763228 36
1790763233 36
1790763238 36
1790763243 36
1790763248 36
1790763253 36
```
</details>

---

