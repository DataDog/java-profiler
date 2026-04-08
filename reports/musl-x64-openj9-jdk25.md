---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-08 13:30:12 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 11 |
| Allocations | 557 |

<details>
<summary>CPU Timeline (3 unique values: 78-87 cores)</summary>

```
1775669122 78
1775669127 78
1775669132 78
1775669137 78
1775669142 78
1775669147 78
1775669152 78
1775669157 83
1775669162 83
1775669167 83
1775669172 83
1775669177 87
1775669182 87
1775669187 87
1775669192 87
1775669197 87
1775669202 87
1775669207 87
1775669212 87
1775669217 87
```
</details>

---

