---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 05:40:09 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (4 unique values: 40-46 cores)</summary>

```
1790156105 46
1790156110 46
1790156115 46
1790156120 46
1790156125 42
1790156130 42
1790156135 40
1790156140 40
1790156145 40
1790156150 40
1790156155 40
1790156160 40
1790156165 46
1790156170 46
1790156175 46
1790156180 46
1790156185 46
1790156190 46
1790156195 46
1790156200 46
```
</details>

---

