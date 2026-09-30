---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 07:18:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 15 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790766822 48
1790766827 48
1790766832 48
1790766837 48
1790766842 48
1790766848 48
1790766853 48
1790766858 48
1790766863 48
1790766868 48
1790766873 48
1790766878 48
1790766883 48
1790766888 48
1790766893 48
1790766898 48
1790766903 48
1790766908 48
1790766913 43
1790766918 43
```
</details>

---

