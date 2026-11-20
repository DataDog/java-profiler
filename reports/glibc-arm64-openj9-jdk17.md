---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 11:32:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 300 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 15 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1795192113 49
1795192118 49
1795192123 49
1795192128 49
1795192133 49
1795192138 49
1795192143 49
1795192148 49
1795192153 49
1795192158 49
1795192163 49
1795192168 49
1795192173 49
1795192178 49
1795192183 49
1795192188 49
1795192193 49
1795192198 64
1795192203 64
1795192208 64
```
</details>

---

