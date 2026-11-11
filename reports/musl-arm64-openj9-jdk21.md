---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 04:41:08 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 259 |
| Sample Rate | 4.32/sec |
| Health Score | 270% |
| Threads | 11 |
| Allocations | 146 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 16 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794389818 36
1794389823 36
1794389828 36
1794389833 36
1794389838 36
1794389843 36
1794389848 36
1794389853 36
1794389858 48
1794389863 48
1794389868 48
1794389873 48
1794389878 48
1794389883 48
1794389888 48
1794389893 48
1794389898 48
1794389903 48
1794389908 48
1794389913 48
```
</details>

---

