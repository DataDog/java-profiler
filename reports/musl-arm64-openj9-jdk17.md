---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 14:06:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 7 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 14 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (2 unique values: 30-39 cores)</summary>

```
1790272848 39
1790272853 30
1790272858 30
1790272863 30
1790272868 30
1790272873 30
1790272878 30
1790272883 30
1790272888 30
1790272893 30
1790272898 30
1790272903 30
1790272908 30
1790272913 30
1790272918 30
1790272923 30
1790272928 30
1790272933 30
1790272938 30
1790272943 30
```
</details>

---

