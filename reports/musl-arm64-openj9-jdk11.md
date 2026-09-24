---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 06:19:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1790244818 40
1790244823 40
1790244828 40
1790244833 40
1790244838 40
1790244843 40
1790244848 40
1790244853 40
1790244858 40
1790244863 40
1790244868 40
1790244873 40
1790244878 40
1790244883 40
1790244888 40
1790244893 40
1790244898 40
1790244903 40
1790244908 40
1790244913 40
```
</details>

---

