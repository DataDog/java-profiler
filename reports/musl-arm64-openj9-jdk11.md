---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 10:44:37 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 9 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1032 |
| Sample Rate | 17.20/sec |
| Health Score | 1075% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790087788 50
1790087793 50
1790087798 50
1790087803 50
1790087808 50
1790087813 50
1790087818 50
1790087823 50
1790087828 50
1790087833 50
1790087838 50
1790087843 50
1790087848 50
1790087853 50
1790087858 50
1790087863 50
1790087868 50
1790087873 50
1790087878 50
1790087883 50
```
</details>

---

