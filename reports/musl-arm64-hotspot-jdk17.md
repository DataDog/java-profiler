---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 07:06:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 10 |
| Allocations | 185 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 15 |
| Allocations | 89 |

<details>
<summary>CPU Timeline (2 unique values: 17-32 cores)</summary>

```
1790074838 17
1790074843 17
1790074848 17
1790074853 17
1790074858 17
1790074863 32
1790074868 32
1790074873 32
1790074878 32
1790074883 32
1790074888 32
1790074893 32
1790074898 32
1790074903 32
1790074908 32
1790074913 32
1790074918 32
1790074923 32
1790074928 32
1790074933 32
```
</details>

---

