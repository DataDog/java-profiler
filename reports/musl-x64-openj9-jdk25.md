---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 11:32:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 11 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795192083 85
1795192088 85
1795192093 85
1795192098 85
1795192103 85
1795192108 85
1795192113 85
1795192118 85
1795192123 85
1795192128 85
1795192133 85
1795192138 85
1795192143 85
1795192148 85
1795192153 85
1795192158 85
1795192163 87
1795192168 87
1795192173 87
1795192178 87
```
</details>

---

