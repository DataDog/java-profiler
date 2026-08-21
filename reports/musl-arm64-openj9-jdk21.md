---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-21 11:10:42 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (5 unique values: 43-48 cores)</summary>

```
1787324712 45
1787324717 45
1787324722 43
1787324727 43
1787324732 43
1787324737 43
1787324742 43
1787324747 43
1787324752 43
1787324757 43
1787324762 43
1787324767 43
1787324772 46
1787324777 46
1787324782 46
1787324787 46
1787324792 44
1787324797 44
1787324802 44
1787324807 44
```
</details>

---

