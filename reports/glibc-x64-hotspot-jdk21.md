---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 10:20:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (3 unique values: 65-69 cores)</summary>

```
1790259161 69
1790259166 69
1790259171 67
1790259176 67
1790259181 67
1790259186 67
1790259191 67
1790259196 67
1790259201 67
1790259206 67
1790259211 69
1790259216 69
1790259221 69
1790259226 69
1790259231 69
1790259236 67
1790259241 67
1790259246 67
1790259251 67
1790259256 65
```
</details>

---

