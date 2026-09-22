---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 07:06:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 153 |
| Sample Rate | 2.55/sec |
| Health Score | 159% |
| Threads | 12 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1790074853 23
1790074858 23
1790074863 23
1790074868 23
1790074873 23
1790074878 23
1790074883 23
1790074888 23
1790074893 23
1790074898 23
1790074903 23
1790074908 23
1790074913 23
1790074918 23
1790074923 28
1790074928 28
1790074933 28
1790074938 28
1790074943 28
1790074948 28
```
</details>

---

