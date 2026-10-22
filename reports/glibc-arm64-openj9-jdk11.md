---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:00:05 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1011 |
| Sample Rate | 16.85/sec |
| Health Score | 1053% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1792670128 48
1792670133 48
1792670138 48
1792670143 48
1792670148 48
1792670153 48
1792670158 48
1792670163 48
1792670168 48
1792670173 48
1792670178 48
1792670183 48
1792670188 48
1792670193 48
1792670198 48
1792670203 48
1792670208 48
1792670213 48
1792670218 48
1792670223 48
```
</details>

---

