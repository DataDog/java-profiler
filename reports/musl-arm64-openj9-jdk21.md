---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:17:59 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 4.85/sec |
| Health Score | 303% |
| Threads | 11 |
| Allocations | 165 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794582728 43
1794582733 43
1794582738 43
1794582743 43
1794582748 43
1794582753 43
1794582758 43
1794582763 43
1794582768 43
1794582773 43
1794582778 48
1794582783 48
1794582788 48
1794582793 48
1794582798 48
1794582803 48
1794582808 48
1794582813 48
1794582818 48
1794582823 48
```
</details>

---

