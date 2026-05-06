---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-06 08:41:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 47-54 cores)</summary>

```
1778071077 54
1778071082 54
1778071087 49
1778071092 49
1778071097 47
1778071102 47
1778071107 47
1778071112 47
1778071117 47
1778071122 47
1778071127 47
1778071132 47
1778071137 47
1778071142 47
1778071147 47
1778071152 47
1778071157 47
1778071162 52
1778071167 52
1778071172 52
```
</details>

---

