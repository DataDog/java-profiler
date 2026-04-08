---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-08 09:54:16 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
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
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1775656141 64
1775656146 64
1775656151 64
1775656156 64
1775656161 64
1775656166 64
1775656171 64
1775656176 64
1775656181 64
1775656186 64
1775656191 64
1775656196 64
1775656201 64
1775656206 64
1775656211 64
1775656216 64
1775656221 64
1775656226 64
1775656231 64
1775656236 64
```
</details>

---

