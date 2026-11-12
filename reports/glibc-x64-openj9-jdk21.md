---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 07:43:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (5 unique values: 86-92 cores)</summary>

```
1794487190 91
1794487195 91
1794487200 91
1794487205 91
1794487210 91
1794487215 91
1794487220 89
1794487225 89
1794487230 89
1794487235 89
1794487240 89
1794487245 89
1794487250 89
1794487255 89
1794487260 89
1794487265 92
1794487270 92
1794487275 86
1794487280 86
1794487285 86
```
</details>

---

